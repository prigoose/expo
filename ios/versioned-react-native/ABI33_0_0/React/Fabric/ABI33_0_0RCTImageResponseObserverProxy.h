/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#import "ABI33_0_0RCTImageResponseDelegate.h"
#import "ABI33_0_0RCTImageResponseDelegate.h"

#include <ReactABI33_0_0/imagemanager/ImageResponseObserver.h>

NS_ASSUME_NONNULL_BEGIN

namespace facebook {
  namespace ReactABI33_0_0 {
    class ABI33_0_0RCTImageResponseObserverProxy: public ImageResponseObserver {
    public:
      ABI33_0_0RCTImageResponseObserverProxy(void* delegate);
      void didReceiveImage(const ImageResponse &imageResponse) override;
      void didReceiveProgress (float p) override;
      void didReceiveFailure() override;
      
    private:
      id<ABI33_0_0RCTImageResponseDelegate> delegate_;
    };
  }
}

NS_ASSUME_NONNULL_END
