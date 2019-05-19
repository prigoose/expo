//
//  ABI33_0_0AIRGMSPolygon.h
//  AirMaps
//
//  Created by Gerardo Pacheco 02/05/2017.
//

#ifdef HAVE_GOOGLE_MAPS

#import <GoogleMaps/GoogleMaps.h>
#import <ReactABI33_0_0/UIView+ReactABI33_0_0.h>

@class ABI33_0_0AIRGoogleMapPolygon;

@interface ABI33_0_0AIRGMSPolygon : GMSPolygon
@property (nonatomic, strong) NSString *identifier;
@property (nonatomic, copy) ABI33_0_0RCTBubblingEventBlock onPress;
@end

#endif
