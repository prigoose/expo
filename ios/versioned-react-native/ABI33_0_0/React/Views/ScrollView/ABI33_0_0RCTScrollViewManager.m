/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "ABI33_0_0RCTScrollViewManager.h"

#import "ABI33_0_0RCTBridge.h"
#import "ABI33_0_0RCTScrollView.h"
#import "ABI33_0_0RCTShadowView.h"
#import "ABI33_0_0RCTUIManager.h"

@interface ABI33_0_0RCTScrollView (Private)

- (NSArray<NSDictionary *> *)calculateChildFramesData;

@end

@implementation ABI33_0_0RCTConvert (UIScrollView)

ABI33_0_0RCT_ENUM_CONVERTER(UIScrollViewKeyboardDismissMode, (@{
  @"none": @(UIScrollViewKeyboardDismissModeNone),
  @"on-drag": @(UIScrollViewKeyboardDismissModeOnDrag),
  @"interactive": @(UIScrollViewKeyboardDismissModeInteractive),
  // Backwards compatibility
  @"onDrag": @(UIScrollViewKeyboardDismissModeOnDrag),
}), UIScrollViewKeyboardDismissModeNone, integerValue)

ABI33_0_0RCT_ENUM_CONVERTER(UIScrollViewIndicatorStyle, (@{
  @"default": @(UIScrollViewIndicatorStyleDefault),
  @"black": @(UIScrollViewIndicatorStyleBlack),
  @"white": @(UIScrollViewIndicatorStyleWhite),
}), UIScrollViewIndicatorStyleDefault, integerValue)

#if defined(__IPHONE_OS_VERSION_MAX_ALLOWED) && __IPHONE_OS_VERSION_MAX_ALLOWED >= 110000 /* __IPHONE_11_0 */
ABI33_0_0RCT_ENUM_CONVERTER(UIScrollViewContentInsetAdjustmentBehavior, (@{
  @"automatic": @(UIScrollViewContentInsetAdjustmentAutomatic),
  @"scrollableAxes": @(UIScrollViewContentInsetAdjustmentScrollableAxes),
  @"never": @(UIScrollViewContentInsetAdjustmentNever),
  @"always": @(UIScrollViewContentInsetAdjustmentAlways),
}), UIScrollViewContentInsetAdjustmentNever, integerValue)
#endif

@end

@implementation ABI33_0_0RCTScrollViewManager

ABI33_0_0RCT_EXPORT_MODULE()

- (UIView *)view
{
  return [[ABI33_0_0RCTScrollView alloc] initWithEventDispatcher:self.bridge.eventDispatcher];
}

ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(alwaysBounceHorizontal, BOOL)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(alwaysBounceVertical, BOOL)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(bounces, BOOL)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(bouncesZoom, BOOL)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(canCancelContentTouches, BOOL)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(centerContent, BOOL)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(maintainVisibleContentPosition, NSDictionary)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(automaticallyAdjustContentInsets, BOOL)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(decelerationRate, CGFloat)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(directionalLockEnabled, BOOL)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(indicatorStyle, UIScrollViewIndicatorStyle)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(keyboardDismissMode, UIScrollViewKeyboardDismissMode)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(maximumZoomScale, CGFloat)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(minimumZoomScale, CGFloat)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(scrollEnabled, BOOL)
#if !TARGET_OS_TV
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(pagingEnabled, BOOL)
ABI33_0_0RCT_REMAP_VIEW_PROPERTY(pinchGestureEnabled, scrollView.pinchGestureEnabled, BOOL)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(scrollsToTop, BOOL)
#endif
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(showsHorizontalScrollIndicator, BOOL)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(showsVerticalScrollIndicator, BOOL)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(scrollEventThrottle, NSTimeInterval)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(zoomScale, CGFloat)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(contentInset, UIEdgeInsets)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(scrollIndicatorInsets, UIEdgeInsets)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(scrollToOverflowEnabled, BOOL)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(snapToInterval, int)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(snapToOffsets, NSArray<NSNumber *>)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(snapToStart, BOOL)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(snapToEnd, BOOL)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(snapToAlignment, NSString)
ABI33_0_0RCT_REMAP_VIEW_PROPERTY(contentOffset, scrollView.contentOffset, CGPoint)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(onScrollBeginDrag, ABI33_0_0RCTDirectEventBlock)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(onScroll, ABI33_0_0RCTDirectEventBlock)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(onScrollToTop, ABI33_0_0RCTDirectEventBlock)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(onScrollEndDrag, ABI33_0_0RCTDirectEventBlock)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(onMomentumScrollBegin, ABI33_0_0RCTDirectEventBlock)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(onMomentumScrollEnd, ABI33_0_0RCTDirectEventBlock)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(DEPRECATED_sendUpdatedChildFrames, BOOL)
#if defined(__IPHONE_OS_VERSION_MAX_ALLOWED) && __IPHONE_OS_VERSION_MAX_ALLOWED >= 110000 /* __IPHONE_11_0 */
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(contentInsetAdjustmentBehavior, UIScrollViewContentInsetAdjustmentBehavior)
#endif

// overflow is used both in css-layout as well as by ReactABI33_0_0-native. In css-layout
// we always want to treat overflow as scroll but depending on what the overflow
// is set to from js we want to clip drawing or not. This piece of code ensures
// that css-layout is always treating the contents of a scroll container as
// overflow: 'scroll'.
ABI33_0_0RCT_CUSTOM_SHADOW_PROPERTY(overflow, ABI33_0_0YGOverflow, ABI33_0_0RCTShadowView) {
#pragma unused (json)
  view.overflow = ABI33_0_0YGOverflowScroll;
}

ABI33_0_0RCT_EXPORT_METHOD(getContentSize:(nonnull NSNumber *)ReactABI33_0_0Tag
                  callback:(ABI33_0_0RCTResponseSenderBlock)callback)
{
  [self.bridge.uiManager addUIBlock:
   ^(__unused ABI33_0_0RCTUIManager *uiManager, NSDictionary<NSNumber *, ABI33_0_0RCTScrollView *> *viewRegistry) {

    ABI33_0_0RCTScrollView *view = viewRegistry[ReactABI33_0_0Tag];
    if (!view || ![view isKindOfClass:[ABI33_0_0RCTScrollView class]]) {
      ABI33_0_0RCTLogError(@"Cannot find ABI33_0_0RCTScrollView with tag #%@", ReactABI33_0_0Tag);
      return;
    }

    CGSize size = view.scrollView.contentSize;
    callback(@[@{
      @"width" : @(size.width),
      @"height" : @(size.height)
    }]);
  }];
}

ABI33_0_0RCT_EXPORT_METHOD(calculateChildFrames:(nonnull NSNumber *)ReactABI33_0_0Tag
                  callback:(ABI33_0_0RCTResponseSenderBlock)callback)
{
  [self.bridge.uiManager addUIBlock:
   ^(__unused ABI33_0_0RCTUIManager *uiManager, NSDictionary<NSNumber *, ABI33_0_0RCTScrollView *> *viewRegistry) {

    ABI33_0_0RCTScrollView *view = viewRegistry[ReactABI33_0_0Tag];
    if (!view || ![view isKindOfClass:[ABI33_0_0RCTScrollView class]]) {
      ABI33_0_0RCTLogError(@"Cannot find ABI33_0_0RCTScrollView with tag #%@", ReactABI33_0_0Tag);
      return;
    }

    NSArray<NSDictionary *> *childFrames = [view calculateChildFramesData];
    if (childFrames) {
      callback(@[childFrames]);
    }
  }];
}

ABI33_0_0RCT_EXPORT_METHOD(scrollTo:(nonnull NSNumber *)ReactABI33_0_0Tag
                  offsetX:(CGFloat)x
                  offsetY:(CGFloat)y
                  animated:(BOOL)animated)
{
  [self.bridge.uiManager addUIBlock:
   ^(__unused ABI33_0_0RCTUIManager *uiManager, NSDictionary<NSNumber *, UIView *> *viewRegistry){
    UIView *view = viewRegistry[ReactABI33_0_0Tag];
    if ([view conformsToProtocol:@protocol(ABI33_0_0RCTScrollableProtocol)]) {
      [(id<ABI33_0_0RCTScrollableProtocol>)view scrollToOffset:(CGPoint){x, y} animated:animated];
    } else {
      ABI33_0_0RCTLogError(@"tried to scrollTo: on non-ABI33_0_0RCTScrollableProtocol view %@ "
                  "with tag #%@", view, ReactABI33_0_0Tag);
    }
  }];
}

ABI33_0_0RCT_EXPORT_METHOD(scrollToEnd:(nonnull NSNumber *)ReactABI33_0_0Tag
                  animated:(BOOL)animated)
{
  [self.bridge.uiManager addUIBlock:
   ^(__unused ABI33_0_0RCTUIManager *uiManager, NSDictionary<NSNumber *, UIView *> *viewRegistry){
     UIView *view = viewRegistry[ReactABI33_0_0Tag];
     if ([view conformsToProtocol:@protocol(ABI33_0_0RCTScrollableProtocol)]) {
       [(id<ABI33_0_0RCTScrollableProtocol>)view scrollToEnd:animated];
     } else {
       ABI33_0_0RCTLogError(@"tried to scrollTo: on non-ABI33_0_0RCTScrollableProtocol view %@ "
                   "with tag #%@", view, ReactABI33_0_0Tag);
     }
   }];
}

ABI33_0_0RCT_EXPORT_METHOD(zoomToRect:(nonnull NSNumber *)ReactABI33_0_0Tag
                  withRect:(CGRect)rect
                  animated:(BOOL)animated)
{
  [self.bridge.uiManager addUIBlock:
   ^(__unused ABI33_0_0RCTUIManager *uiManager, NSDictionary<NSNumber *, UIView *> *viewRegistry){
    UIView *view = viewRegistry[ReactABI33_0_0Tag];
    if ([view conformsToProtocol:@protocol(ABI33_0_0RCTScrollableProtocol)]) {
      [(id<ABI33_0_0RCTScrollableProtocol>)view zoomToRect:rect animated:animated];
    } else {
      ABI33_0_0RCTLogError(@"tried to zoomToRect: on non-ABI33_0_0RCTScrollableProtocol view %@ "
                  "with tag #%@", view, ReactABI33_0_0Tag);
    }
  }];
}

ABI33_0_0RCT_EXPORT_METHOD(flashScrollIndicators:(nonnull NSNumber *)ReactABI33_0_0Tag)
{
  [self.bridge.uiManager addUIBlock:
   ^(__unused ABI33_0_0RCTUIManager *uiManager, NSDictionary<NSNumber *, ABI33_0_0RCTScrollView *> *viewRegistry){

     ABI33_0_0RCTScrollView *view = viewRegistry[ReactABI33_0_0Tag];
     if (!view || ![view isKindOfClass:[ABI33_0_0RCTScrollView class]]) {
       ABI33_0_0RCTLogError(@"Cannot find ABI33_0_0RCTScrollView with tag #%@", ReactABI33_0_0Tag);
       return;
     }

     [view.scrollView flashScrollIndicators];
   }];
}

@end
