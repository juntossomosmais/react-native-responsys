
#import "RNResponsysBridge.h"
#import <PushIOManager/PushIOManager.h>

@implementation RNResponsysBridge

- (dispatch_queue_t)methodQueue
{
    return dispatch_get_main_queue();
}

+ (void)startWithAPIKey:(NSString *)key andAccountToken:(NSString*)token {
    [PushIOManager sharedInstance].configType = PIOConfigTypeRelease; //load pushio_config.json
#ifdef DEBUG
    [[PushIOManager sharedInstance] enableLogging:YES];
    [[PushIOManager sharedInstance] setLogLevel:PIOLogLevelInfo]; //PIOLogLevelWarn or PIOLogLevelError
#else
    [[PushIOManager sharedInstance] disableLogging];
#endif
    
    NSError *error = nil;
    [[PushIOManager sharedInstance] configureWithAPIKey:key accountToken:token error:&error];
    
    if(nil != error){
        NSLog(@"PushIO - Unable to configure SDK, reason: %@", error.description);
    }
}

RCT_EXPORT_MODULE()

RCT_EXPORT_METHOD(registerUserId:(NSString *)userId) {
    [[PushIOManager sharedInstance] registerUserID:userId];
}

RCT_EXPORT_METHOD(trackEvent:(NSString *)eventName) {
    [[PushIOManager sharedInstance] trackEvent:eventName];
}

@end
  
