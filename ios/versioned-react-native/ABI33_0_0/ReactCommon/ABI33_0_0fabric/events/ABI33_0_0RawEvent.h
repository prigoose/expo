/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <memory>

#include <folly/dynamic.h>
#include <ABI33_0_0jsi/ABI33_0_0jsi.h>
#include <ReactABI33_0_0/events/primitives.h>

namespace facebook {
namespace ReactABI33_0_0 {

/*
 * Represents ready-to-dispatch event object.
 */
class RawEvent {
 public:
  RawEvent(
      std::string type,
      ValueFactory payloadFactory,
      SharedEventTarget eventTarget);

  const std::string type;
  const ValueFactory payloadFactory;
  const SharedEventTarget eventTarget;
};

} // namespace ReactABI33_0_0
} // namespace facebook
