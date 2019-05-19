/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ABI33_0_0ImageLocalData.h"

#include <ReactABI33_0_0/components/image/conversions.h>
#include <ReactABI33_0_0/debug/debugStringConvertibleUtils.h>

namespace facebook {
namespace ReactABI33_0_0 {

ImageSource ImageLocalData::getImageSource() const {
  return imageSource_;
}

const ImageRequest &ImageLocalData::getImageRequest() const {
  return imageRequest_;
}

#pragma mark - DebugStringConvertible

#if RN_DEBUG_STRING_CONVERTIBLE
std::string ImageLocalData::getDebugName() const {
  return "ImageLocalData";
}

SharedDebugStringConvertibleList ImageLocalData::getDebugProps() const {
  return {debugStringConvertibleItem("imageSource", imageSource_)};
}
#endif

} // namespace ReactABI33_0_0
} // namespace facebook
