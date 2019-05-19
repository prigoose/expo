//
//  ABI33_0_0AIRGoogleMapURLTileManager.m
//  Created by Nick Italiano on 11/5/16.
//

#ifdef HAVE_GOOGLE_MAPS

#import "ABI33_0_0AIRGoogleMapUrlTileManager.h"
#import "ABI33_0_0AIRGoogleMapUrlTile.h"

@interface ABI33_0_0AIRGoogleMapUrlTileManager()

@end

@implementation ABI33_0_0AIRGoogleMapUrlTileManager

ABI33_0_0RCT_EXPORT_MODULE()

- (UIView *)view
{
  ABI33_0_0AIRGoogleMapUrlTile *tileLayer = [ABI33_0_0AIRGoogleMapUrlTile new];
  return tileLayer;
}

ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(urlTemplate, NSString)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(zIndex, int)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(maximumZ, NSInteger)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(minimumZ, NSInteger)
ABI33_0_0RCT_EXPORT_VIEW_PROPERTY(flipY, BOOL)

@end

#endif
