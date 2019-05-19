/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
#include "ABI33_0_0YGLayout.h"
#include "ABI33_0_0Utils.h"

using namespace facebook;

bool ABI33_0_0YGLayout::operator==(ABI33_0_0YGLayout layout) const {
  bool isEqual = ABI33_0_0YGFloatArrayEqual(position, layout.position) &&
      ABI33_0_0YGFloatArrayEqual(dimensions, layout.dimensions) &&
      ABI33_0_0YGFloatArrayEqual(margin, layout.margin) &&
      ABI33_0_0YGFloatArrayEqual(border, layout.border) &&
      ABI33_0_0YGFloatArrayEqual(padding, layout.padding) &&
      direction == layout.direction && hadOverflow == layout.hadOverflow &&
      lastOwnerDirection == layout.lastOwnerDirection &&
      nextCachedMeasurementsIndex == layout.nextCachedMeasurementsIndex &&
      cachedLayout == layout.cachedLayout &&
      computedFlexBasis == layout.computedFlexBasis;

  for (uint32_t i = 0; i < ABI33_0_0YG_MAX_CACHED_RESULT_COUNT && isEqual; ++i) {
    isEqual = isEqual && cachedMeasurements[i] == layout.cachedMeasurements[i];
  }

  if (!ABI33_0_0yoga::isUndefined(measuredDimensions[0]) ||
      !ABI33_0_0yoga::isUndefined(layout.measuredDimensions[0])) {
    isEqual =
        isEqual && (measuredDimensions[0] == layout.measuredDimensions[0]);
  }
  if (!ABI33_0_0yoga::isUndefined(measuredDimensions[1]) ||
      !ABI33_0_0yoga::isUndefined(layout.measuredDimensions[1])) {
    isEqual =
        isEqual && (measuredDimensions[1] == layout.measuredDimensions[1]);
  }

  return isEqual;
}
