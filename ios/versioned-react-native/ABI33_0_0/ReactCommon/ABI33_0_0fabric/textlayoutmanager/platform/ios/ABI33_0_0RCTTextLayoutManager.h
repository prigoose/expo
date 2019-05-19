/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <UIKit/UIKit.h>

#import <ReactABI33_0_0/attributedstring/AttributedString.h>
#import <ReactABI33_0_0/attributedstring/ParagraphAttributes.h>
#import <ReactABI33_0_0/core/LayoutConstraints.h>
#import <ReactABI33_0_0/graphics/Geometry.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * iOS-specific TextLayoutManager
 */
@interface ABI33_0_0RCTTextLayoutManager : NSObject

- (facebook::ReactABI33_0_0::Size)
    measureWithAttributedString:
        (facebook::ReactABI33_0_0::AttributedString)attributedString
            paragraphAttributes:
                (facebook::ReactABI33_0_0::ParagraphAttributes)paragraphAttributes
              layoutConstraints:
                  (facebook::ReactABI33_0_0::LayoutConstraints)layoutConstraints;

- (void)drawAttributedString:(facebook::ReactABI33_0_0::AttributedString)attributedString
         paragraphAttributes:
             (facebook::ReactABI33_0_0::ParagraphAttributes)paragraphAttributes
                       frame:(CGRect)frame;

- (facebook::ReactABI33_0_0::SharedEventEmitter)
    getEventEmitterWithAttributeString:
        (facebook::ReactABI33_0_0::AttributedString)attributedString
                   paragraphAttributes:
                       (facebook::ReactABI33_0_0::ParagraphAttributes)paragraphAttributes
                                 frame:(CGRect)frame
                               atPoint:(CGPoint)point;

@end

NS_ASSUME_NONNULL_END
