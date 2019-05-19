/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <CoreGraphics/CoreGraphics.h>

#import <Foundation/Foundation.h>

/**
 * These block types can be used for mapping input event handlers from JS to view
 * properties. Unlike JS method callbacks, these can be called multiple times.
 */
typedef void (^ABI33_0_0RCTDirectEventBlock)(NSDictionary *body);
typedef void (^ABI33_0_0RCTBubblingEventBlock)(NSDictionary *body);

/**
 * Logical node in a tree of application components. Both `ShadowView` and
 * `UIView` conforms to this. Allows us to write utilities that reason about
 * trees generally.
 */
@protocol ABI33_0_0RCTComponent <NSObject>

@property (nonatomic, copy) NSNumber *ReactABI33_0_0Tag;

- (void)insertReactABI33_0_0Subview:(id<ABI33_0_0RCTComponent>)subview atIndex:(NSInteger)atIndex;
- (void)removeReactABI33_0_0Subview:(id<ABI33_0_0RCTComponent>)subview;
- (NSArray<id<ABI33_0_0RCTComponent>> *)ReactABI33_0_0Subviews;
- (id<ABI33_0_0RCTComponent>)ReactABI33_0_0Superview;
- (NSNumber *)ReactABI33_0_0TagAtPoint:(CGPoint)point;

// View/ShadowView is a root view
- (BOOL)isReactABI33_0_0RootView;

/**
 * Called each time props have been set.
 * Not all props have to be set - ReactABI33_0_0 can set only changed ones.
 * @param changedProps String names of all set props.
 */
- (void)didSetProps:(NSArray<NSString *> *)changedProps;

/**
 * Called each time subviews have been updated
 */
- (void)didUpdateReactABI33_0_0Subviews;

@end

// TODO: this is kinda dumb - let's come up with a
// better way of identifying root ReactABI33_0_0 views please!
static inline BOOL ABI33_0_0RCTIsReactABI33_0_0RootView(NSNumber *ReactABI33_0_0Tag)
{
  return ReactABI33_0_0Tag.integerValue % 10 == 1;
}
