/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <memory>

#include <ReactABI33_0_0/attributedstring/AttributedString.h>
#include <ReactABI33_0_0/attributedstring/ParagraphAttributes.h>
#include <ReactABI33_0_0/core/LayoutConstraints.h>
#include <ReactABI33_0_0/uimanager/ContextContainer.h>

namespace facebook {
namespace ReactABI33_0_0 {

class TextLayoutManager;

using SharedTextLayoutManager = std::shared_ptr<const TextLayoutManager>;

/*
 * Cross platform facade for iOS-specific ABI33_0_0RCTTTextLayoutManager.
 */
class TextLayoutManager {
 public:
  TextLayoutManager(const SharedContextContainer &contextContainer);
  ~TextLayoutManager();

  /*
   * Measures `attributedString` using native text rendering infrastructure.
   */
  Size measure(
      AttributedString attributedString,
      ParagraphAttributes paragraphAttributes,
      LayoutConstraints layoutConstraints) const;

  /*
   * Returns an opaque pointer to platform-specific TextLayoutManager.
   * Is used on a native views layer to delegate text rendering to the manager.
   */
  void *getNativeTextLayoutManager() const;

 private:
  void *self_;
};

} // namespace ReactABI33_0_0
} // namespace facebook
