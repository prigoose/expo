/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "ABI33_0_0RCTDeviceInfo.h"

#import "ABI33_0_0RCTAccessibilityManager.h"
#import "ABI33_0_0RCTAssert.h"
#import "ABI33_0_0RCTEventDispatcher.h"
#import "ABI33_0_0RCTUIUtils.h"
#import "ABI33_0_0RCTUtils.h"

@implementation ABI33_0_0RCTDeviceInfo {
#if !TARGET_OS_TV
  UIInterfaceOrientation _currentInterfaceOrientation;
  NSDictionary *_currentInterfaceDimensions;
#endif
}

@synthesize bridge = _bridge;

ABI33_0_0RCT_EXPORT_MODULE()

+ (BOOL)requiresMainQueueSetup
{
  return YES;
}

- (dispatch_queue_t)methodQueue
{
  return dispatch_get_main_queue();
}

- (void)setBridge:(ABI33_0_0RCTBridge *)bridge
{
  _bridge = bridge;

  [[NSNotificationCenter defaultCenter] addObserver:self
                                           selector:@selector(didReceiveNewContentSizeMultiplier)
                                               name:ABI33_0_0RCTAccessibilityManagerDidUpdateMultiplierNotification
                                             object:_bridge.accessibilityManager];
#if !TARGET_OS_TV
  _currentInterfaceOrientation = [ABI33_0_0RCTSharedApplication() statusBarOrientation];

  [[NSNotificationCenter defaultCenter] addObserver:self
                                           selector:@selector(interfaceOrientationDidChange)
                                               name:UIApplicationDidChangeStatusBarOrientationNotification
                                             object:nil];

  _currentInterfaceDimensions = ABI33_0_0RCTExportedDimensions(_bridge);

  [[NSNotificationCenter defaultCenter] addObserver:self
                                           selector:@selector(interfaceFrameDidChange)
                                               name:UIApplicationDidBecomeActiveNotification
                                             object:nil];
#endif
}

static BOOL ABI33_0_0RCTIsIPhoneX() {
  static BOOL isIPhoneX = NO;
  static dispatch_once_t onceToken;

  dispatch_once(&onceToken, ^{
    ABI33_0_0RCTAssertMainQueue();

    CGSize screenSize = [UIScreen mainScreen].nativeBounds.size;
    CGSize iPhoneXScreenSize = CGSizeMake(1125, 2436);
    CGSize iPhoneXMaxScreenSize = CGSizeMake(1242, 2688);
    CGSize iPhoneXRScreenSize = CGSizeMake(828, 1792);

    isIPhoneX =
      CGSizeEqualToSize(screenSize, iPhoneXScreenSize) ||
      CGSizeEqualToSize(screenSize, iPhoneXMaxScreenSize) ||
      CGSizeEqualToSize(screenSize, iPhoneXRScreenSize);
  });

  return isIPhoneX;
}

static NSDictionary *ABI33_0_0RCTExportedDimensions(ABI33_0_0RCTBridge *bridge)
{
  ABI33_0_0RCTAssertMainQueue();

  ABI33_0_0RCTDimensions dimensions = ABI33_0_0RCTGetDimensions(bridge.accessibilityManager.multiplier);
  typeof (dimensions.window) window = dimensions.window;
  NSDictionary<NSString *, NSNumber *> *dimsWindow = @{
      @"width": @(window.width),
      @"height": @(window.height),
      @"scale": @(window.scale),
      @"fontScale": @(window.fontScale)
  };
  typeof (dimensions.screen) screen = dimensions.screen;
  NSDictionary<NSString *, NSNumber *> *dimsScreen = @{
      @"width": @(screen.width),
      @"height": @(screen.height),
      @"scale": @(screen.scale),
      @"fontScale": @(screen.fontScale)
  };
  return @{
      @"window": dimsWindow,
      @"screen": dimsScreen
  };
}

- (void)dealloc
{
  [NSNotificationCenter.defaultCenter removeObserver:self];
}

- (void)invalidate
{
  ABI33_0_0RCTExecuteOnMainQueue(^{
    self->_bridge = nil;
    [[NSNotificationCenter defaultCenter] removeObserver:self];
  });
}

- (NSDictionary<NSString *, id> *)constantsToExport
{
  return [self getConstants];
}

- (NSDictionary<NSString *, id> *)getConstants
{
  return @{
    @"Dimensions": ABI33_0_0RCTExportedDimensions(_bridge),
    // Note:
    // This prop is deprecated and will be removed in a future release.
    // Please use this only for a quick and temporary solution.
    // Use <SafeAreaView> instead.
    @"isIPhoneX_deprecated": @(ABI33_0_0RCTIsIPhoneX()),
  };
}

- (void)didReceiveNewContentSizeMultiplier
{
  ABI33_0_0RCTBridge *bridge = _bridge;
  ABI33_0_0RCTExecuteOnMainQueue(^{
    // Report the event across the bridge.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    [bridge.eventDispatcher sendDeviceEventWithName:@"didUpdateDimensions"
                                        body:ABI33_0_0RCTExportedDimensions(bridge)];
#pragma clang diagnostic pop
  });
}

#if !TARGET_OS_TV

- (void)interfaceOrientationDidChange
{
  __weak typeof(self) weakSelf = self;
  ABI33_0_0RCTExecuteOnMainQueue(^{
    [weakSelf _interfaceOrientationDidChange];
  });
}


- (void)_interfaceOrientationDidChange
{
  UIInterfaceOrientation nextOrientation = [ABI33_0_0RCTSharedApplication() statusBarOrientation];

  // Update when we go from portrait to landscape, or landscape to portrait
  if ((UIInterfaceOrientationIsPortrait(_currentInterfaceOrientation) &&
       !UIInterfaceOrientationIsPortrait(nextOrientation)) ||
      (UIInterfaceOrientationIsLandscape(_currentInterfaceOrientation) &&
       !UIInterfaceOrientationIsLandscape(nextOrientation))) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
        [_bridge.eventDispatcher sendDeviceEventWithName:@"didUpdateDimensions"
                                                    body:ABI33_0_0RCTExportedDimensions(_bridge)];
#pragma clang diagnostic pop
      }

  _currentInterfaceOrientation = nextOrientation;
}


- (void)interfaceFrameDidChange
{
  __weak typeof(self) weakSelf = self;
  ABI33_0_0RCTExecuteOnMainQueue(^{
    [weakSelf _interfaceFrameDidChange];
  });
}


- (void)_interfaceFrameDidChange
{
  NSDictionary *nextInterfaceDimensions = ABI33_0_0RCTExportedDimensions(_bridge);

  if (!([nextInterfaceDimensions isEqual:_currentInterfaceDimensions])) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
      [_bridge.eventDispatcher sendDeviceEventWithName:@"didUpdateDimensions"
                                                  body:nextInterfaceDimensions];
#pragma clang diagnostic pop
  }

  _currentInterfaceDimensions = nextInterfaceDimensions;
}

#endif // TARGET_OS_TV


@end
