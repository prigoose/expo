/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <Foundation/Foundation.h>

#import <ReactABI33_0_0/ABI33_0_0RCTDefines.h>

@protocol ABI33_0_0RCTReloadListener
- (void)didReceiveReloadCommand;
@end

/** Registers a weakly-held observer of the Command+R reload key command. */
ABI33_0_0RCT_EXTERN void ABI33_0_0RCTRegisterReloadCommandListener(id<ABI33_0_0RCTReloadListener> listener);

/** Triggers a reload for all current listeners. You shouldn't need to use this directly in most cases. */
ABI33_0_0RCT_EXTERN void ABI33_0_0RCTTriggerReloadCommandListeners(void);
