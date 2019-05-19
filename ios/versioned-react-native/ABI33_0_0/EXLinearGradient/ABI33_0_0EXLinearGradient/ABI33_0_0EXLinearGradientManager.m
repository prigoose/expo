// Copyright 2015-present 650 Industries. All rights reserved.

#import <ABI33_0_0EXLinearGradient/ABI33_0_0EXLinearGradientManager.h>
#import <ABI33_0_0EXLinearGradient/ABI33_0_0EXLinearGradient.h>
#import <ABI33_0_0UMCore/ABI33_0_0UMUIManager.h>

@interface ABI33_0_0EXLinearGradientManager ()

@end

@implementation ABI33_0_0EXLinearGradientManager

ABI33_0_0UM_EXPORT_MODULE(ABI33_0_0EXLinearGradientManager);

- (NSString *)viewName
{
  return @"ExpoLinearGradient";
}

- (UIView *)view
{
  return [[ABI33_0_0EXLinearGradient alloc] init];
}

ABI33_0_0UM_VIEW_PROPERTY(colors, NSArray *, ABI33_0_0EXLinearGradient) {
  [view setColors:value];
}

// NOTE: startPoint and endPoint assume that the value is an array with exactly two floats

ABI33_0_0UM_VIEW_PROPERTY(startPoint, NSArray *, ABI33_0_0EXLinearGradient) {
  CGPoint point = CGPointMake([[value objectAtIndex:0] floatValue], [[value objectAtIndex:1] floatValue]);
  [view setStartPoint:point];
}

ABI33_0_0UM_VIEW_PROPERTY(endPoint, NSArray *, ABI33_0_0EXLinearGradient) {
  CGPoint point = CGPointMake([[value objectAtIndex:0] floatValue], [[value objectAtIndex:1] floatValue]);
  [view setEndPoint:point];
}

ABI33_0_0UM_VIEW_PROPERTY(locations, NSArray *, ABI33_0_0EXLinearGradient) {
  [view setLocations:value];
}

@end
