
#if __has_include("RCTBridgeModule.h")
#import "RCTBridgeModule.h"
#else
#import <React/RCTBridgeModule.h>
#endif

@interface RNResponsysBridge : NSObject <RCTBridgeModule>

+ (void)startWithAPIKey:(NSString *)key andAccountToken:(NSString*)token;

@end
  
