//  Copyright © 2018-present 650 Industries. All rights reserved.

#import "ABI33_0_0EXExpoUserNotificationCenterProxy.h"

@interface ABI33_0_0EXExpoUserNotificationCenterProxy ()

@property (nonatomic, weak) id<ABI33_0_0UMUserNotificationCenterProxyInterface> userNotificationCenter;

@end

@implementation ABI33_0_0EXExpoUserNotificationCenterProxy

- (instancetype)initWithUserNotificationCenter:(id<ABI33_0_0UMUserNotificationCenterProxyInterface>)userNotificationCenter
{
  if (self = [super init]) {
    _userNotificationCenter = userNotificationCenter;
  }
  return self;
}

+ (const NSArray<Protocol *> *)exportedInterfaces
{
  return @[@protocol(ABI33_0_0UMUserNotificationCenterProxyInterface)];
}

- (void)getNotificationSettingsWithCompletionHandler:(void(^)(UNNotificationSettings *settings))completionHandler
{
  [_userNotificationCenter getNotificationSettingsWithCompletionHandler:completionHandler];
}

- (void)requestAuthorizationWithOptions:(UNAuthorizationOptions)options completionHandler:(void (^)(BOOL granted, NSError *__nullable error))completionHandler
{
  [_userNotificationCenter requestAuthorizationWithOptions:options completionHandler:completionHandler];
}

@end
