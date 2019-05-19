/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ABI33_0_0ImageRequest.h"

namespace facebook {
namespace ReactABI33_0_0 {

ImageRequest::ImageRequest(const ImageSource &imageSource)
    : imageSource_(imageSource) {
  // Not implemented.
}

ImageRequest::ImageRequest(ImageRequest &&other) noexcept
    : imageSource_(std::move(other.imageSource_)),
      coordinator_(std::move(other.coordinator_)) {
  // Not implemented.
}

ImageRequest::~ImageRequest() {
  // Not implemented.
}

const ImageResponseObserverCoordinator *ImageRequest::getObserverCoordinator()
    const {
  // Not implemented
  abort();
}

} // namespace ReactABI33_0_0
} // namespace facebook
