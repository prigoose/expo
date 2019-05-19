// Copyright 2016-present 650 Industries. All rights reserved.

#import <ABI33_0_0EXAppAuth/ABI33_0_0EXAppAuthAppDelegate.h>
#import <ABI33_0_0UMCore/ABI33_0_0UMAppDelegateWrapper.h>
#import <ABI33_0_0EXAppAuth/ABI33_0_0EXAppAuthSessionsManager.h>
#import <ABI33_0_0UMCore/ABI33_0_0UMModuleRegistryProvider.h>

@implementation ABI33_0_0EXAppAuthAppDelegate

ABI33_0_0UM_REGISTER_SINGLETON_MODULE(ABI33_0_0EXAppAuthAppDelegate)

- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options
{
  return [(ABI33_0_0EXAppAuthSessionsManager *)[ABI33_0_0UMModuleRegistryProvider getSingletonModuleForClass:ABI33_0_0EXAppAuthSessionsManager.class] application:app openURL:url options:options];
}

@end
