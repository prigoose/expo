/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <UIKit/UIKit.h>

@interface UIView (Private)

// remove clipped subviews implementation
- (void)ReactABI33_0_0_remountAllSubviews;
- (void)ReactABI33_0_0_updateClippedSubviewsWithClipRect:(CGRect)clipRect relativeToView:(UIView *)clipView;
- (UIView *)ReactABI33_0_0_findClipView;

@end
