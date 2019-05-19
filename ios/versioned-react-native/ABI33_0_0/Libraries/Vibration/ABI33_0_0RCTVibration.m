/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "ABI33_0_0RCTVibration.h"

#import <AudioToolbox/AudioToolbox.h>

@implementation ABI33_0_0RCTVibration

ABI33_0_0RCT_EXPORT_MODULE()

ABI33_0_0RCT_EXPORT_METHOD(vibrate)
{
  AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
}

@end
