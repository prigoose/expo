/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <ReactABI33_0_0/components/image/ImageProps.h>
#include <ReactABI33_0_0/components/image/conversions.h>
#include <ReactABI33_0_0/core/propsConversions.h>

namespace facebook {
namespace ReactABI33_0_0 {

ImageProps::ImageProps(const ImageProps &sourceProps, const RawProps &rawProps)
    : ViewProps(sourceProps, rawProps),
      sources(convertRawProp(rawProps, "source", sourceProps.sources)),
      defaultSources(convertRawProp(
          rawProps,
          "defaultSource",
          sourceProps.defaultSources)),
      resizeMode(convertRawProp(
          rawProps,
          "resizeMode",
          sourceProps.resizeMode,
          ImageResizeMode::Stretch)),
      blurRadius(
          convertRawProp(rawProps, "blurRadius", sourceProps.blurRadius)),
      capInsets(convertRawProp(rawProps, "capInsets", sourceProps.capInsets)),
      tintColor(convertRawProp(rawProps, "tintColor", sourceProps.tintColor)) {}

} // namespace ReactABI33_0_0
} // namespace facebook
