/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <vector>
#include "ABI33_0_0CompactValue.h"
#include "ABI33_0_0Yoga.h"

using ABI33_0_0YGVector = std::vector<ABI33_0_0YGNodeRef>;

ABI33_0_0YG_EXTERN_C_BEGIN

WIN_EXPORT float ABI33_0_0YGRoundValueToPixelGrid(
    const float value,
    const float pointScaleFactor,
    const bool forceCeil,
    const bool forceFloor);

ABI33_0_0YG_EXTERN_C_END

namespace facebook {
namespace ABI33_0_0yoga {

inline bool isUndefined(float value) {
  return std::isnan(value);
}

} // namespace ABI33_0_0yoga
} // namespace facebook

using namespace facebook;

extern const std::array<ABI33_0_0YGEdge, 4> trailing;
extern const std::array<ABI33_0_0YGEdge, 4> leading;
extern bool ABI33_0_0YGValueEqual(const ABI33_0_0YGValue a, const ABI33_0_0YGValue b);
extern const ABI33_0_0YGValue ABI33_0_0YGValueUndefined;
extern const ABI33_0_0YGValue ABI33_0_0YGValueAuto;
extern const ABI33_0_0YGValue ABI33_0_0YGValueZero;

struct ABI33_0_0YGCachedMeasurement {
  float availableWidth;
  float availableHeight;
  ABI33_0_0YGMeasureMode widthMeasureMode;
  ABI33_0_0YGMeasureMode heightMeasureMode;

  float computedWidth;
  float computedHeight;

  ABI33_0_0YGCachedMeasurement()
      : availableWidth(0),
        availableHeight(0),
        widthMeasureMode((ABI33_0_0YGMeasureMode) -1),
        heightMeasureMode((ABI33_0_0YGMeasureMode) -1),
        computedWidth(-1),
        computedHeight(-1) {}

  bool operator==(ABI33_0_0YGCachedMeasurement measurement) const {
    bool isEqual = widthMeasureMode == measurement.widthMeasureMode &&
        heightMeasureMode == measurement.heightMeasureMode;

    if (!ABI33_0_0yoga::isUndefined(availableWidth) ||
        !ABI33_0_0yoga::isUndefined(measurement.availableWidth)) {
      isEqual = isEqual && availableWidth == measurement.availableWidth;
    }
    if (!ABI33_0_0yoga::isUndefined(availableHeight) ||
        !ABI33_0_0yoga::isUndefined(measurement.availableHeight)) {
      isEqual = isEqual && availableHeight == measurement.availableHeight;
    }
    if (!ABI33_0_0yoga::isUndefined(computedWidth) ||
        !ABI33_0_0yoga::isUndefined(measurement.computedWidth)) {
      isEqual = isEqual && computedWidth == measurement.computedWidth;
    }
    if (!ABI33_0_0yoga::isUndefined(computedHeight) ||
        !ABI33_0_0yoga::isUndefined(measurement.computedHeight)) {
      isEqual = isEqual && computedHeight == measurement.computedHeight;
    }

    return isEqual;
  }
};

// This value was chosen based on empiracle data. Even the most complicated
// layouts should not require more than 16 entries to fit within the cache.
#define ABI33_0_0YG_MAX_CACHED_RESULT_COUNT 16

namespace facebook {
namespace ABI33_0_0yoga {
namespace detail {

template <size_t Size>
class Values {
private:
  std::array<CompactValue, Size> values_;

public:
  Values() = default;
  explicit Values(const ABI33_0_0YGValue& defaultValue) noexcept {
    values_.fill(defaultValue);
  }

  const CompactValue& operator[](size_t i) const noexcept {
    return values_[i];
  }
  CompactValue& operator[](size_t i) noexcept {
    return values_[i];
  }

  template <size_t I>
  ABI33_0_0YGValue get() const noexcept {
    return std::get<I>(values_);
  }

  template <size_t I>
  void set(ABI33_0_0YGValue& value) noexcept {
    std::get<I>(values_) = value;
  }

  template <size_t I>
  void set(ABI33_0_0YGValue&& value) noexcept {
    set<I>(value);
  }

  bool operator==(const Values& other) const noexcept {
    for (size_t i = 0; i < Size; ++i) {
      if (values_[i] != other.values_[i]) {
        return false;
      }
    }
    return true;
  }

  Values& operator=(const Values& other) = default;
};

} // namespace detail
} // namespace ABI33_0_0yoga
} // namespace facebook

static const float kDefaultFlexGrow = 0.0f;
static const float kDefaultFlexShrink = 0.0f;
static const float kWebDefaultFlexShrink = 1.0f;

extern bool ABI33_0_0YGFloatsEqual(const float a, const float b);
extern bool ABI33_0_0YGValueEqual(const ABI33_0_0YGValue a, const ABI33_0_0YGValue b);
extern facebook::ABI33_0_0yoga::detail::CompactValue ABI33_0_0YGComputedEdgeValue(
    const facebook::ABI33_0_0yoga::detail::Values<
        facebook::ABI33_0_0yoga::enums::count<ABI33_0_0YGEdge>()>& edges,
    ABI33_0_0YGEdge edge,
    facebook::ABI33_0_0yoga::detail::CompactValue defaultValue);
