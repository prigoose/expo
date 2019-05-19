/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <Foundation/Foundation.h>

#import <ReactABI33_0_0/ABI33_0_0RCTBridgeMethod.h>
#import <cxxReactABI33_0_0/ABI33_0_0CxxModule.h>

@interface ABI33_0_0RCTCxxMethod : NSObject <ABI33_0_0RCTBridgeMethod>

- (instancetype)initWithCxxMethod:(const facebook::xplat::module::CxxModule::Method &)cxxMethod;

@end
