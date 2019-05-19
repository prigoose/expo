/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <functional>
#include <memory>

#include <folly/Hash.h>
#include <folly/Optional.h>
#include <ReactABI33_0_0/attributedstring/TextAttributes.h>
#include <ReactABI33_0_0/core/Sealable.h>
#include <ReactABI33_0_0/core/ShadowNode.h>
#include <ReactABI33_0_0/debug/DebugStringConvertible.h>
#include <ReactABI33_0_0/mounting/ShadowView.h>

namespace facebook {
namespace ReactABI33_0_0 {

class AttributedString;

using SharedAttributedString = std::shared_ptr<const AttributedString>;

/*
 * Simple, cross-platfrom, ReactABI33_0_0-specific implementation of attributed string
 * (aka spanned string).
 * `AttributedString` is basically a list of `Fragments` which have `string` and
 * `textAttributes` + `shadowNode` associated with the `string`.
 */
class AttributedString : public Sealable, public DebugStringConvertible {
 public:
  class Fragment {
   public:
    std::string string;
    TextAttributes textAttributes;
    ShadowView shadowView;
    ShadowView parentShadowView;

    bool operator==(const Fragment &rhs) const;
    bool operator!=(const Fragment &rhs) const;
  };

  using Fragments = std::vector<Fragment>;

  /*
   * Appends and prepends a `fragment` to the string.
   */
  void appendFragment(const Fragment &fragment);
  void prependFragment(const Fragment &fragment);

  /*
   * Appends and prepends an `attributedString` (all its fragments) to
   * the string.
   */
  void appendAttributedString(const AttributedString &attributedString);
  void prependAttributedString(const AttributedString &attributedString);

  /*
   * Returns read-only reference to a list of fragments.
   */
  const Fragments &getFragments() const;

  /*
   * Returns a string constructed from all strings in all fragments.
   */
  std::string getString() const;

  bool operator==(const AttributedString &rhs) const;
  bool operator!=(const AttributedString &rhs) const;

#pragma mark - DebugStringConvertible

#if RN_DEBUG_STRING_CONVERTIBLE
  SharedDebugStringConvertibleList getDebugChildren() const override;
#endif

 private:
  Fragments fragments_;
};

} // namespace ReactABI33_0_0
} // namespace facebook

namespace std {
template <>
struct hash<facebook::ReactABI33_0_0::AttributedString::Fragment> {
  size_t operator()(
      const facebook::ReactABI33_0_0::AttributedString::Fragment &fragment) const {
    auto seed = size_t{0};
    folly::hash::hash_combine(
        seed,
        fragment.string,
        fragment.textAttributes,
        fragment.shadowView,
        fragment.parentShadowView);
    return seed;
  }
};

template <>
struct hash<facebook::ReactABI33_0_0::AttributedString> {
  size_t operator()(
      const facebook::ReactABI33_0_0::AttributedString &attributedString) const {
    auto seed = size_t{0};

    for (const auto &fragment : attributedString.getFragments()) {
      folly::hash::hash_combine(seed, fragment);
    }

    return seed;
  }
};
} // namespace std
