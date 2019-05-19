// Copyright © 2018 650 Industries. All rights reserved.

#import <ABI33_0_0UMReactNativeAdapter/ABI33_0_0UMModuleRegistryAdapter.h>

@interface ABI33_0_0EXScopedModuleRegistryAdapter : ABI33_0_0UMModuleRegistryAdapter

- (ABI33_0_0UMModuleRegistry *)moduleRegistryForParams:(NSDictionary *)params forExperienceId:(NSString *)experienceId withKernelServices:(NSDictionary *)kernelServices;

@end
