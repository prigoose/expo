// Copyright 2016-present 650 Industries. All rights reserved.

#import <Foundation/Foundation.h>
#import <ABI33_0_0UMCore/ABI33_0_0UMExportedModule.h>
#import <ABI33_0_0UMCore/ABI33_0_0UMModuleRegistryConsumer.h>
#import <ABI33_0_0UMCore/ABI33_0_0UMEventEmitter.h>
#import <ABI33_0_0UMFileSystemInterface/ABI33_0_0UMFileSystemInterface.h>

@interface ABI33_0_0EXFileSystem : ABI33_0_0UMExportedModule <ABI33_0_0UMEventEmitter, ABI33_0_0UMModuleRegistryConsumer, ABI33_0_0UMFileSystemInterface>

@property (nonatomic, readonly) NSString *documentDirectory;
@property (nonatomic, readonly) NSString *cachesDirectory;
@property (nonatomic, readonly) NSString *bundleDirectory;

- (instancetype)initWithDocumentDirectory:(NSString *)documentDirectory cachesDirectory:(NSString *)cachesDirectory bundleDirectory:(NSString *)bundleDirectory;

- (ABI33_0_0UMFileSystemPermissionFlags)permissionsForURI:(NSURL *)uri;

- (BOOL)ensureDirExistsWithPath:(NSString *)path;
- (NSString *)generatePathInDirectory:(NSString *)directory withExtension:(NSString *)extension;

@end

@protocol ABI33_0_0EXFileSystemHandler

+ (void)getInfoForFile:(NSURL *)fileUri
           withOptions:(NSDictionary *)optionxs
              resolver:(ABI33_0_0UMPromiseResolveBlock)resolve
              rejecter:(ABI33_0_0UMPromiseRejectBlock)reject;
+ (void)copyFrom:(NSURL *)from
              to:(NSURL *)to
        resolver:(ABI33_0_0UMPromiseResolveBlock)resolve
        rejecter:(ABI33_0_0UMPromiseRejectBlock)reject;


@end


@interface NSData (ABI33_0_0EXFileSystem)

- (NSString *)md5String;

@end
