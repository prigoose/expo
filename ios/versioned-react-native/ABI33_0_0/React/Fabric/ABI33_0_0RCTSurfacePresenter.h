/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <UIKit/UIKit.h>
#import <memory>

#import <ReactABI33_0_0/ABI33_0_0RCTBridge.h>
#import <ReactABI33_0_0/ABI33_0_0RCTComponentViewFactory.h>
#import <ReactABI33_0_0/uimanager/ContextContainer.h>
#import <ReactABI33_0_0/ABI33_0_0RCTPrimitives.h>
#import <ReactABI33_0_0/config/ReactABI33_0_0NativeConfig.h>

NS_ASSUME_NONNULL_BEGIN

@class ABI33_0_0RCTFabricSurface;
@class ABI33_0_0RCTMountingManager;

/**
 * Coordinates presenting of ReactABI33_0_0 Native Surfaces and represents application
 * facing interface of running ReactABI33_0_0 Native core.
 * SurfacePresenter incapsulates a bridge object inside and discourage direct
 * access to it.
 */
@interface ABI33_0_0RCTSurfacePresenter : NSObject

- (instancetype)initWithBridge:(ABI33_0_0RCTBridge *)bridge
                        config:(std::shared_ptr<const facebook::ReactABI33_0_0::ReactABI33_0_0NativeConfig>)config;

@property (nonatomic, readonly) ABI33_0_0RCTComponentViewFactory *componentViewFactory;
@property (nonatomic, readonly) facebook::ReactABI33_0_0::SharedContextContainer contextContainer;

@end

@interface ABI33_0_0RCTSurfacePresenter (Surface)

/**
 * Surface uses these methods to register itself in the Presenter.
 */
- (void)registerSurface:(ABI33_0_0RCTFabricSurface *)surface;
/**
 * Starting initiates running, rendering and mounting processes.
 * Should be called after registerSurface and any other surface-specific setup is done
 */
- (void)startSurface:(ABI33_0_0RCTFabricSurface *)surface;
- (void)unregisterSurface:(ABI33_0_0RCTFabricSurface *)surface;
- (void)setProps:(NSDictionary *)props
         surface:(ABI33_0_0RCTFabricSurface *)surface;

- (nullable ABI33_0_0RCTFabricSurface *)surfaceForRootTag:(ReactABI33_0_0Tag)rootTag;

/**
 * Measures the Surface with given constraints.
 */
- (CGSize)sizeThatFitsMinimumSize:(CGSize)minimumSize
                      maximumSize:(CGSize)maximumSize
                          surface:(ABI33_0_0RCTFabricSurface *)surface;

/**
 * Sets `minimumSize` and `maximumSize` layout constraints for the Surface.
 */
- (void)setMinimumSize:(CGSize)minimumSize
           maximumSize:(CGSize)maximumSize
               surface:(ABI33_0_0RCTFabricSurface *)surface;

@end

@interface ABI33_0_0RCTSurfacePresenter (Deprecated)

/**
 * Returns a underlying bridge.
 */
- (ABI33_0_0RCTBridge *)bridge_DO_NOT_USE;

@end

@interface ABI33_0_0RCTBridge (Deprecated)

@property (nonatomic) ABI33_0_0RCTSurfacePresenter *surfacePresenter;

@end

NS_ASSUME_NONNULL_END
