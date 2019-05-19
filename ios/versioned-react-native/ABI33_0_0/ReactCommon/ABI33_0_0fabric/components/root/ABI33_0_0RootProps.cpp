/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ABI33_0_0RootProps.h"

#include <ReactABI33_0_0/components/view/YogaLayoutableShadowNode.h>
#include <ReactABI33_0_0/components/view/conversions.h>

namespace facebook {
namespace ReactABI33_0_0 {

static ABI33_0_0YGStyle ABI33_0_0yogaStyleFromLayoutConstraints(
    const LayoutConstraints &layoutConstraints) {
  auto ABI33_0_0yogaStyle = ABI33_0_0YGStyle{};
  ABI33_0_0yogaStyle.minDimensions[ABI33_0_0YGDimensionWidth] =
      ABI33_0_0yogaStyleValueFromFloat(layoutConstraints.minimumSize.width);
  ABI33_0_0yogaStyle.minDimensions[ABI33_0_0YGDimensionHeight] =
      ABI33_0_0yogaStyleValueFromFloat(layoutConstraints.minimumSize.height);

  ABI33_0_0yogaStyle.maxDimensions[ABI33_0_0YGDimensionWidth] =
      ABI33_0_0yogaStyleValueFromFloat(layoutConstraints.maximumSize.width);
  ABI33_0_0yogaStyle.maxDimensions[ABI33_0_0YGDimensionHeight] =
      ABI33_0_0yogaStyleValueFromFloat(layoutConstraints.maximumSize.height);

  ABI33_0_0yogaStyle.direction =
      ABI33_0_0yogaDirectionFromLayoutDirection(layoutConstraints.layoutDirection);

  return ABI33_0_0yogaStyle;
}

RootProps::RootProps(
    const RootProps &sourceProps,
    const LayoutConstraints &layoutConstraints,
    const LayoutContext &layoutContext)
    : ViewProps(ABI33_0_0yogaStyleFromLayoutConstraints(layoutConstraints)),
      layoutConstraints(layoutConstraints),
      layoutContext(layoutContext){};

} // namespace ReactABI33_0_0
} // namespace facebook
