//
//  BranchContentMetadata+RNBranch.m
//  Branch-SDK
//
//  Created by Jimmy Dee on 12/6/17.
//

#import "ABI33_0_0BranchContentMetadata+RNBranch.h"
#import "ABI33_0_0NSObject+RNBranch.h"
#import "ABI33_0_0RNBranchProperty.h"

@implementation BranchContentMetadata(ABI33_0_0RNBranch)

+ (NSDictionary<NSString *,ABI33_0_0RNBranchProperty *> *)supportedProperties
{
    static NSDictionary<NSString *, ABI33_0_0RNBranchProperty *> *_properties;
    static dispatch_once_t once = 0;
    dispatch_once(&once, ^{
        _properties =
        @{
          @"contentSchema": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setContentSchema:) type:NSString.class],
          @"quantity": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setQuantityWithNumber:) type:NSNumber.class],
          @"price": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setPriceWithString:) type:NSString.class],
          @"currency": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setCurrency:) type:NSString.class],
          @"sku": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setSku:) type:NSString.class],
          @"productName": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setProductName:) type:NSString.class],
          @"productBrand": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setProductBrand:) type:NSString.class],
          @"productCategory": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setProductCategory:) type:NSString.class],
          @"productVariant": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setProductVariant:) type:NSString.class],
          @"condition": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setCondition:) type:NSString.class],
          @"ratingAverage": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setRatingAverageWithNumber:) type:NSNumber.class],
          @"ratingCount": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setRatingCountWithNumber:) type:NSNumber.class],
          @"ratingMax": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setRatingMaxWithNumber:) type:NSNumber.class],
          @"addressStreet": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setAddressStreet:) type:NSString.class],
          @"addressCity": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setAddressCity:) type:NSString.class],
          @"addressRegion": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setAddressRegion:) type:NSString.class],
          @"addressCountry": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setAddressCountry:) type:NSString.class],
          @"addressPostalCode": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setAddressPostalCode:) type:NSString.class],
          @"latitude": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setLatitudeWithNumber:) type:NSNumber.class],
          @"longitude": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setLongitudeWithNumber:) type:NSNumber.class],
          @"imageCaptions": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setImageCaptionsWithArray:) type:NSArray.class],
          @"customMetadata": [ABI33_0_0RNBranchProperty propertyWithSetterSelector:@selector(setCustomMetadataWithDictionary:) type:NSDictionary.class]
          };
    });
    
    return _properties;
}

- (instancetype)initWithMap:(NSDictionary *)map
{
    self = [self init];
    if (self) {
        [self setSupportedPropertiesWithMap:map];
    }
    return self;
}

- (void)setQuantityWithNumber:(NSNumber *)quantity
{
    self.quantity = quantity.doubleValue;
}

- (void)setPriceWithString:(NSString *)price
{
    self.price = [NSDecimalNumber decimalNumberWithString:price];
}

- (void)setRatingAverageWithNumber:(NSNumber *)ratingAverage
{
    self.ratingAverage = ratingAverage.doubleValue;
}

- (void)setRatingCountWithNumber:(NSNumber *)ratingCount
{
    self.ratingCount = ratingCount.integerValue;
}

- (void)setRatingMaxWithNumber:(NSNumber *)ratingMax
{
    self.ratingMax = ratingMax.doubleValue;
}

- (void)setLatitudeWithNumber:(NSNumber *)latitude
{
    self.latitude = latitude.doubleValue;
}

- (void)setLongitudeWithNumber:(NSNumber *)longitude
{
    self.longitude = longitude.doubleValue;
}

- (void)setImageCaptionsWithArray:(NSArray *)imageCaptions
{
    self.imageCaptions = imageCaptions.mutableCopy;
}

- (void)setCustomMetadataWithDictionary:(NSDictionary *)customMetadata
{
    self.customMetadata = customMetadata.mutableCopy;
}

@end
