// Copyright 2016-present 650 Industries. All rights reserved.

#import <ABI33_0_0EXPermissions/ABI33_0_0EXRemoteNotificationRequester.h>
#import <ABI33_0_0UMCore/ABI33_0_0UMUtilities.h>
#import <ABI33_0_0EXPermissions/ABI33_0_0EXUserNotificationRequester.h>

NSString * const ABI33_0_0EXAppDidRegisterForRemoteNotificationsNotificationName = @"kEXAppDidRegisterForRemoteNotificationsNotification";

@interface ABI33_0_0EXRemoteNotificationRequester ()

@property (nonatomic, strong) ABI33_0_0UMPromiseResolveBlock resolve;
@property (nonatomic, strong) ABI33_0_0UMPromiseRejectBlock reject;
@property (nonatomic, weak) id<ABI33_0_0EXPermissionRequesterDelegate> delegate;
@property (nonatomic, assign) BOOL remoteNotificationsRegistrationIsPending;
@property (nonatomic, strong) ABI33_0_0EXUserNotificationRequester *localNotificationRequester;
@property (nonatomic, weak) ABI33_0_0UMModuleRegistry *moduleRegistry;

@end

@implementation ABI33_0_0EXRemoteNotificationRequester

- (instancetype)initWithModuleRegistry: (ABI33_0_0UMModuleRegistry *) moduleRegistry {
  if (self = [super init]) {
    _remoteNotificationsRegistrationIsPending = NO;
    _moduleRegistry = moduleRegistry;
  }
  return self;
}

+ (NSDictionary *)permissionsWithModuleRegistry:(ABI33_0_0UMModuleRegistry *)moduleRegistry
{
  __block ABI33_0_0EXPermissionStatus status;
  [ABI33_0_0UMUtilities performSynchronouslyOnMainThread:^{
    status = (ABI33_0_0UMSharedApplication().isRegisteredForRemoteNotifications) ?
    ABI33_0_0EXPermissionStatusGranted :
    ABI33_0_0EXPermissionStatusUndetermined;
  }];
  NSMutableDictionary *permissions = [[ABI33_0_0EXUserNotificationRequester permissionsWithModuleRegistry:moduleRegistry] mutableCopy];
  [permissions setValuesForKeysWithDictionary:@{
                                                @"status": [ABI33_0_0EXPermissions permissionStringForStatus:status],
                                                @"expires": ABI33_0_0EXPermissionExpiresNever,
                                                }];
  return permissions;
}

- (void)requestPermissionsWithResolver:(ABI33_0_0UMPromiseResolveBlock)resolve rejecter:(ABI33_0_0UMPromiseRejectBlock)reject
{
  if (_resolve != nil || _reject != nil) {
    reject(@"E_AWAIT_PROMISE", @"Another request for the same permission is already being handled.", nil);
    return;
  }

  _resolve = resolve;
  _reject = reject;

  BOOL __block isRegisteredForRemoteNotifications = NO;
  [ABI33_0_0UMUtilities performSynchronouslyOnMainThread:^{
    isRegisteredForRemoteNotifications = ABI33_0_0UMSharedApplication().isRegisteredForRemoteNotifications;
  }];

  if (isRegisteredForRemoteNotifications) {
    // resolve immediately if already registered
    [self _maybeConsumeResolverWithCurrentPermissions];
  } else {
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(_handleDidRegisterForRemoteNotifications:)
                                                 name:ABI33_0_0EXAppDidRegisterForRemoteNotificationsNotificationName
                                               object:nil];
    _localNotificationRequester = [[ABI33_0_0EXUserNotificationRequester alloc] initWithModuleRegistry:_moduleRegistry];
    [_localNotificationRequester setDelegate:self];
    [_localNotificationRequester requestPermissionsWithResolver:nil rejecter:nil];
    _remoteNotificationsRegistrationIsPending = YES;
    dispatch_async(dispatch_get_main_queue(), ^{
      [ABI33_0_0UMSharedApplication() registerForRemoteNotifications];
    });
  }
}

- (void)setDelegate:(id<ABI33_0_0EXPermissionRequesterDelegate>)delegate
{
  _delegate = delegate;
}

- (void)dealloc
{
  [self _clearObserver];
}

- (void)_handleDidRegisterForRemoteNotifications:(__unused NSNotification *)notif
{
  [self _clearObserver];
  id<ABI33_0_0EXPermissionsModule> permissionsModule = [_moduleRegistry getModuleImplementingProtocol:@protocol(ABI33_0_0EXPermissionsModule)];
  NSAssert(permissionsModule, @"Permissions module is required to properly consume result.");
  __weak typeof(self) weakSelf = self;
  dispatch_async(permissionsModule.methodQueue, ^{
    [weakSelf _maybeConsumeResolverWithCurrentPermissions];
  });
}

- (void)_clearObserver
{
  [[NSNotificationCenter defaultCenter] removeObserver:self];
  _remoteNotificationsRegistrationIsPending = NO;
}

- (void)_maybeConsumeResolverWithCurrentPermissions
{
  if (_localNotificationRequester == nil && !_remoteNotificationsRegistrationIsPending) {
    if (_resolve) {
      _resolve([[self class] permissionsWithModuleRegistry:_moduleRegistry]);
      _resolve = nil;
      _reject = nil;
    }
    if (_delegate) {
      [_delegate permissionRequesterDidFinish:self];
    }
  }
}

# pragma mark - ABI33_0_0EXPermissionRequesterDelegate

- (void)permissionRequesterDidFinish:(NSObject<ABI33_0_0EXPermissionRequester> *)requester
{
  if (requester == _localNotificationRequester) {
    _localNotificationRequester = nil;
    NSString *localNotificationsStatus = [[ABI33_0_0EXUserNotificationRequester permissionsWithModuleRegistry:_moduleRegistry] objectForKey:@"status"];
    // We may assume that `ABI33_0_0EXLocalNotificationRequester`'s permission request will always finish
    // when the user responds to the dialog or has already responded in the past.
    // However, `UIApplication.registerForRemoteNotification` results in calling
    // `application:didRegisterForRemoteNotificationsWithDeviceToken:` or
    // `application:didFailToRegisterForRemoteNotificationsWithError:` on the application delegate
    // ONLY when the notifications are enabled in settings (by allowing sound, alerts or app badge).
    // So, when the local notifications are disabled, the application delegate's callbacks will not be called instantly.
    if ([localNotificationsStatus isEqualToString:[ABI33_0_0EXPermissions permissionStringForStatus:ABI33_0_0EXPermissionStatusDenied]]) {
      [self _clearObserver];
    }
    [self _maybeConsumeResolverWithCurrentPermissions];
  }
}

@end
