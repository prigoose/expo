/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <ReactABI33_0_0/components/view/ViewEventEmitter.h>

namespace facebook {
namespace ReactABI33_0_0 {

class ImageEventEmitter : public ViewEventEmitter {
 public:
  using ViewEventEmitter::ViewEventEmitter;

  void onLoadStart() const;
  void onLoad() const;
  void onLoadEnd() const;
  void onProgress(double) const;
  void onError() const;
  void onPartialLoad() const;
};

} // namespace ReactABI33_0_0
} // namespace facebook
