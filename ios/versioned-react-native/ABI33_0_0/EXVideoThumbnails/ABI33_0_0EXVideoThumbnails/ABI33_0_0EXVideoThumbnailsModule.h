//  Copyright © 2018 650 Industries. All rights reserved.
#import <ABI33_0_0UMCore/ABI33_0_0UMExportedModule.h>
#import <ABI33_0_0UMCore/ABI33_0_0UMModuleRegistryConsumer.h>
#import <ABI33_0_0UMFileSystemInterface/ABI33_0_0UMFileSystemInterface.h>

@interface ABI33_0_0EXVideoThumbnailsModule : ABI33_0_0UMExportedModule <ABI33_0_0UMModuleRegistryConsumer>

@property (nonatomic, weak) ABI33_0_0UMModuleRegistry *moduleRegistry;
@property (nonatomic, weak) id<ABI33_0_0UMFileSystemInterface> fileSystem;

@end
