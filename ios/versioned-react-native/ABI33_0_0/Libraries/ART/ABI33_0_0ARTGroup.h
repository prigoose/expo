/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <Foundation/Foundation.h>

#import "ABI33_0_0ARTContainer.h"
#import "ABI33_0_0ARTNode.h"

@interface ABI33_0_0ARTGroup : ABI33_0_0ARTNode <ABI33_0_0ARTContainer>

@property (nonatomic, assign) CGRect clipping;

@end
