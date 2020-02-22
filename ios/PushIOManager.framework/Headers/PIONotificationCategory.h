//
//  PIONotificationCategory.h
//  PushIOManager
//
//  Copyright © 2017 Oracle Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PIONotificationCategory : NSObject

@property (nonatomic, strong) NSString *identifier;
@property (nonatomic, strong) NSArray *actions;

-(id)initWithIdentifier:(NSString *)identifier actions:(NSArray *)actions;

@end

@interface PIONotificationAction : NSObject

@property (nonatomic, strong) NSString *identifier;
@property (nonatomic, strong) NSString *title;
@property (nonatomic, assign) BOOL isDestructive;
@property (nonatomic, assign) BOOL isForeground;
@property (nonatomic, assign) BOOL authenticationRequired;

-(id)initWithIdentifier:(NSString *)identifier title:(NSString *)title isDestructive:(BOOL)isDestructive isForeground:(BOOL)isForeground authenticationRequired:(BOOL)authenticationRequired;

@end
