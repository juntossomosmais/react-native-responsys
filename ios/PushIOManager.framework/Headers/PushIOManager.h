//
//  PushIOManager.h
//  PushIOManager
//
//  Copyright © 2009-2017 Oracle. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "PIOPreference.h"

#ifndef __IPHONE_10_0
# define __IPHONE_10_0  100000
#endif

#if defined(__IPHONE_10_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_10_0
#import <UserNotifications/UserNotifications.h>
#endif


FOUNDATION_EXPORT NSString * const PIOMCRawResponseCaptureNotification;
FOUNDATION_EXPORT NSString * const PIOMCRawResponseValue;
FOUNDATION_EXPORT NSString * const PIOMCRequestURL;



/**-----------------------------------------------------------------------------
 * @name Metadata Handler APIs
 * -----------------------------------------------------------------------------
 */


/**
 PushIOPushMetaHandler delegate implementation indicates that application will handle the metadata from the push and the SDK should take no further action.
 */
@protocol PushIOPushMetaHandler <NSObject>

@optional

/**
 If application doesn't implement, nothing will be done when audio names are present.
 If application return NO, the SDK will attempt to load and play the given audio file, searching for it by name in the application bundle.
 NOTE: To play the sound, application must include the AVFoundation framework.
 @param audioFileName  The name of the audio file that has been passed in the push notification.
 
 @return returns YES if application handled the audio play, NO otherwise.
 */
- (BOOL) handlePushAudio:(NSString *) audioFileName;


/**
 If application doesn't implement, nothing will happen when alert text is available in push.
 If application returns NO, then an alert will be presented with the given alert text and no title.
 
 @param alertText The text for an alert passed in the push.
 
 @return returns YES if application handled the alert text, NO otherwise.
 */
- (BOOL) handlePushAlert:(NSString *) alertText;


/**
 If application doesn't implement, nothing will happen when badge value is present.
 If application returns NO, then the SDK will update the application badge with the badge value.
 
 @param updatedApplicatonBadge The badge included updated values for the application badge.
 
 @return returns YES if application handled the badge value, NO otherwise.
 */
- (BOOL) handlePushBadgeUpdate:(NSString *)updatedApplicatonBadge;


/**
 If you do not implement this method, or return NO, then a full-screen UIWebView will be brought up and load the contents of the URL.
 If the URL had been shortened by the PushIO servers, this will pass the expanded URL.
 
 @param urlString URL sent as part of the push notification.
 
 @return returns YES if application handled the URL, NO otherwise.
 */
- (BOOL) handlePushURL:(NSString *) urlString;


/**
 This will additionally pass along a push token if included, which can be used to identify what data has been fetched
 If this method is not implemented no remote data will be fetched.
 
 
 @param remoteData The push included a link to some external data - that data has been loaded, and is included in the remoteData.
 @param token      device token
 
 @return If application return NO, the SDK will not take any action.
 */
- (BOOL) handlePushExtendedData:(NSData *)remoteData withCustomPushToken:(NSString *)token;


/**
 The push notification payload including a token string for further processing.
 
 @param token device token string.
 
 @return If you return NO, the library will not take action.
 */
- (BOOL) handleCustomPushToken:(NSString *)token;

@end


/**
 @deprecated This method is deprecated starting from version 6.32.0
 @note Please use @code PIOLogLevel @endcode instead.
 
 Help setting the logging level for PushIOManager - the default is "ERRORS_ONLY"
 
 - PUSHIO_DEBUG_NONE:        disable debug.
 - PUSHIO_DEBUG_ERRORS_ONLY: debug error only.
 - PUSHIO_DEBUG_ACTIVITY:    debug activities.
 - PUSHIO_DEBUG_VERBOSE:     debug verbose.
 */
__attribute__((deprecated)) typedef enum {
    PUSHIO_DEBUG_NONE = 0,
    PUSHIO_DEBUG_ERRORS_ONLY = 1,
    PUSHIO_DEBUG_ACTIVITY = 2,
    PUSHIO_DEBUG_VERBOSE = 3
}PushIODebugLevel;


/**
 Help setting the logging level for PushIOManager.
 
 - PIOLogLevelNone:     Log level none
 - PIOLogLevelError:    Log level Error only.
 - PIOLogLevelWarn:     Log level warnings.
 - PIOLogLevelInfo:     Log level informative.
 */
typedef NS_ENUM(NSInteger, PIOLogLevel) {
    PIOLogLevelNone = 0,
    PIOLogLevelError = 1,
    PIOLogLevelWarn = 2,
    PIOLogLevelInfo = 3
};


/**
 Helps setting the application build configuration type (Debug/Release).
 
 - PIOConfigTypeNone:     Configuration type None.
 - PIOConfigTypeDebug:    Configuration type Debug.
 - PIOConfigTypeRelease:  Configuration type Release.
 */
typedef NS_ENUM(NSInteger, PIOConfigType) {
    PIOConfigTypeNone = 0,
    PIOConfigTypeDebug = 1,
    PIOConfigTypeRelease = 2
};


/**
 Encapsulate the list of engagements.
 
 - PUSHIO_ENGAGEMENT_METRIC_LAUNCH:          Engagement type Launch.
 - PUSHIO_ENGAGEMENT_METRIC_PREMIUM_CONTENT: Engagement type Premium.
 - PUSHIO_ENGAGEMENT_METRIC_SOCIAL:          Engagement type Social.
 - PUSHIO_ENGAGEMENT_METRIC_ACTION:          Engagement type Action.
 */
typedef enum {
    PUSHIO_ENGAGEMENT_METRIC_LAUNCH = 0,  // Push IO internal use
    PUSHIO_ENGAGEMENT_METRIC_ACTIVE_SESSION = 1, // Push IO internal use
    PUSHIO_ENGAGEMENT_METRIC_INAPP_PURCHASE = 2,
    PUSHIO_ENGAGEMENT_METRIC_PREMIUM_CONTENT = 3,
    PUSHIO_ENGAGEMENT_METRIC_SOCIAL = 4,
    PUSHIO_ENGAGEMENT_METRIC_ACTION = 5, // Push IO internal use
    PUSHIO_ENGAGEMENT_METRIC_OTHER = 6, // Push IO internal use
}PushIOEngagementMetrics;


//Error Domains
FOUNDATION_EXPORT NSString * const PIOErrorDomainNoNetwork;
FOUNDATION_EXPORT NSString * const PIOErrorDomainMaximumRetryReach;
FOUNDATION_EXPORT NSString * const PIOErrorDomainInvalidURL;

/**
 Error code enum

 - PIOErrorCodeNoNetwork: No network available.
 - PIOErrorCodeMaximumRetryReached: Maximum retry for the web communication reached.
 - PIOErrorCodeInvalidURL: Invalid URL.
 */
typedef NS_ENUM(NSInteger, PIOErrorCode) {
    PIOErrorCodeNoNetwork = 5001,
    PIOErrorCodeMaximumRetryReached,
    PIOErrorCodeInvalidURL,
    PIOErrorCodeInvalidPayload,
    PIOErrorCodeEmptyResponse
};

/**
 Callback used for asynchronous communication between application and PushIO SDK.
 
 @param error    placeholder to populate the error code/reason when operation completed.
 @param response detailed response message.
 */
typedef void (^PIOCompletionHandler)(NSError *error, NSString *response);


/**
 MessageCenter callback used for asynchronous communication between application and PushIO SDK.
 
 @param error    placeholder to populate the error code/reason when operation completed.
 @param messages List of messages fetched. If messages are empty check the error for more details.
 */
typedef void (^PIOMessageCenterCompletionHandler)(NSError *error, NSArray *messages);


/**
 Block (callback) to provide extra event properties at run time.
 
 @param event dictionary containing event's information.
 
 */
typedef NSDictionary* (^PIOGlobalPropertiesBlock)(NSDictionary *event);


/**
 A `PushIOManagerDelegate` implementation ensures to get called back with the progress/completion of registration. Also, lets application know if Newsstand content is available.
 */
@protocol PushIOManagerDelegate <NSObject>

@optional


/**
 Called when PushIO SDK has valid token and ready to send a registration to PushIO server.
 */
- (void)readyForRegistration;


/**
 Called when App has registered with PushIO server successfully.
 */
- (void)registrationSucceeded;


/**
 Called when App failed to register with PushIO server.
 
 @param error      placeholder to populate the error code/reason if registration fails.
 @param statusCode contains the integer value of status code received from server.
 */
- (void)registrationFailedWithError:(NSError *)error statusCode:(int)statusCode;


/**
 Called when PushIO SDK found that Newsstand content is ready.
 */
- (void)newNewsstandContentAvailable;


/**
 SDK has extracted a push dictionary, the metadata is ready to be retrieved.
 */
- (void)pushProcessed;


@end


/**
 `PushIOManager` provides primary interface for application to interact with PushIO SDK. Once registration is complete all Push related operations unlocked to use . i.e.: inApp messaging, Notification preferences, categories handling, engagement reporting etc.
 */

@interface PushIOManager : NSObject


/**-----------------------------------------------------------------------------
 * @name Initializing and Delegation
 * -----------------------------------------------------------------------------
 */


/**
 Initialize `PushIOManager` (as singleton)
 
 @return instance of PushIOManager
 */
+ (PushIOManager *)sharedInstance;


/**
 Event properties that are provided by application which becomes part of every event created.
 */
@property(nonatomic, strong) NSDictionary *globalEventProperties;


/**
 Custom callback to access event properties at run time. Called every time new event is created and provides window for application to determine and provide event properties.
 */
@property (nonatomic, copy) PIOGlobalPropertiesBlock globalEventPropertiesBlock;


/**
 @deprecated This method is deprecated starting from version 6.32.0
 @note Please use @code setLogLevel: @endcode instead.
 
 debugLevel enable different stage of logging with possible values: PUSHIO_DEBUG_NONE, PUSHIO_DEBUG_ERRORS_ONLY,PUSHIO_DEBUG_ACTIVITY, PUSHIO_DEBUG_VERBOSE.
 */
@property (nonatomic, assign) PushIODebugLevel debugLevel __attribute__((deprecated));

/**
 @deprecated This method is deprecated starting from version 6.32.0
 @note Please use registration method with completionHandler and error placeholder as parameter instead.
 
 'PushIOManagerDelegate' keeps application informed about the status of registration as:
 - when SDK is ready for registration 'readyForRegistration' notified.
 - when registration successfully completes 'registrationSucceeded' notified.
 - when registration fails to register 'registrationFailedWithError' is called with error object and status code received from PushIO server.
 */
@property (nonatomic, weak) id <PushIOManagerDelegate> delegate __attribute__((deprecated));


/**
 Status of application registration with SDK.
 */
@property (nonatomic, assign) BOOL registrationStored;


/**
 Allows the application to specify an External Device Tracking ID.
 Stored in persistence storage.
 Set nil to remove the external device tracking identifier.
 */
@property (nonatomic, strong) NSString *externalDeviceTrackingID;


/**
 Allows the application to specify an IDFA programatically.
 Stored in persistence storage.
 Set nil to remove the advertising identifier.
 */
@property (nonatomic, strong) NSString *advertisingIdentifier;


/**
 Allows the application to get the callback when SDK is ready for registration.
 Called when SDK receives the device token successfully.
 */
@property (nonatomic, strong) PIOCompletionHandler readyForRegistrationCompHandler;


/**
 When the value is set to PIOConfigTypeRelease, the SDK performs the 'release' type API key validation.
 When the value is set to PIOConfigTypeDebug, the SDK performs the 'debug' type API key validation.
 When the value is set to PIOConfigTypeNone, the SDK tries to determine the current config and read the configurations from respective pushio_config_debug.json or pushio_config.json and performs the API Key validation.
 */
@property (nonatomic, assign) PIOConfigType configType;

#if defined(__IPHONE_10_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_10_0

/**
 UNUserNotificationDelegates
 userNotificationCenter:willPresentNotification:withCompletionHandler need the presentation options to complete the notification.
 If not provided developer needs to call completion handler in userNotificationCenter:willPresentNotification:withCompletionHandler with notification presentation value.
 */
@property (nonatomic, assign) UNNotificationPresentationOptions notificationPresentationOptions;

#endif

/**-----------------------------------------------------------------------------
 * @name Console Log Printing
 * -----------------------------------------------------------------------------
 */


/**
 Start printing log in debug console. Different level of logging can be enabled with this.
 
 @param enable determines if SDK needs to enable logging.
 
 */
- (void) enableLogging:(BOOL)enable;


/**
 Stop printing log in debug console.
 */
- (void) disableLogging;


/**
 Sets the log level.

 @param logLevel log level
 */
-(void) setLogLevel:(PIOLogLevel)logLevel;


/**
 Check if log printing is enabled in debug console..
 
 @return TRUE if log printing enabled, FALSE otherwise.
 */
- (BOOL)isLoggingEnabled;


/**-----------------------------------------------------------------------------
 * @name SDK setup methods
 * -----------------------------------------------------------------------------
 */


/**
 Validates the key against the current configuration and makes SDK ready for registration for valid API-Key.
 
 @param apiKey       generated in RI portal and used to configure SDK.
 @param accountToken generated in RI portal and used to configure SDK.
 @param error        placeholder to populate the error code/reason if provided API-key is invalid.
 
 @return TRUE if SDK configured successfully (or provided APIKey is valid), FALSE otherwise.
 */
- (BOOL)configureWithAPIKey:(NSString *)apiKey accountToken:(NSString *)accountToken error:(NSError *__autoreleasing *)error;


/**-----------------------------------------------------------------------------
 * @name Registration
 * -----------------------------------------------------------------------------
 */

/**
 After application is configured successfully, it has to register to let server know about the application's metadata/properties.
 
 @param error             placeholder to populate the error code/reason if registration fails.
 @param completionHandler callback to notify when registration is completed with the server.
 
 @return TRUE if register event created and stored successfully, FALSE otherwise.
 @warning return value indicates the registration event creation locally, and completion handler gets called when sync of registration happen with server.
 */
- (BOOL)registerApp:(NSError *__autoreleasing *)error completionHandler:(PIOCompletionHandler)completionHandler;


/**
 @deprecated This method is deprecated starting from version 6.32.0
 @note Please use @code registerApp: completionHandler: @endcode instead.
 
 Register application with server. Loads the API key from pushio_config or pushio_config_debug for production or development respectively.
 Call registerForAllRemoteNotificationTypes internally to get notification access permissions.
 */
- (void)registerWithPushIO __attribute__((deprecated));


/**
 Asks user permissions for all push notifications types. i.e.: Sound/Badge/Alert types.
 If readyForRegistrationCompHandler is not set, then provided completionHandler is assigned to it, to let application have access when SDK receives deviceToken.

 @param completionHandler callback with response for notification permission prompt.

 */
- (void)registerForAllRemoteNotificationTypes:(PIOCompletionHandler)completionHandler;


/**
 Register for all available notification types and with categories.

 @param categories Array of categories to register with.
 @param completionHandler Notify when registration complete.
 */
- (void)registerForAllRemoteNotificationTypesWithCategories:(NSArray *)categories completionHandler:(PIOCompletionHandler)completionHandler;


/**
 @deprecated This method is deprecated starting from version 6.32.0
 @note Please use @code registerForAllRemoteNotificationTypes: completionHandler: @endcode instead.
 
 Ask user to provide the permissions for different notifications i.e.: Sound/Badge/Alert types.
 */
- (void)registerForAllRemoteNotificationTypes __attribute__((deprecated));


/**
 Unregisters the application (create the unregister event and sync with server) from PushIO SDK and no further events are tracked till application register again.
 
 @param error             placeholder to populate the error code/reason if unregister fail.
 @param completionHandler callback to notify when unregister complete with server.
 
 @return TRUE if unregister event created and stored successfully, FALSE otherwise.
 @warning return value indicates the unregister event creation locally, and completion handler gets called when sync of unregister happen with server.
 */
- (BOOL)unregisterApp:(NSError *__autoreleasing *)error completionHandler:(PIOCompletionHandler)completionHandler;


/**
 @deprecated This method is deprecated starting from version 6.32.0
 @note Please use @code unregisterApp: completionHandler: @endcode instead.
 
 Unregister (delete) application from server.
 */
- (void)unregisterFromPushIO __attribute__((deprecated));


/**-----------------------------------------------------------------------------
 * @name Event Trackers
 * -----------------------------------------------------------------------------
 */


/**
 Captures custom events. Application can set extra values related to the custom event via globalEventProperties and globalEventPropertiesCallback.
 
 @param eventName name of the event to be tracked.
 */
- (void)trackEvent:(NSString *)eventName;


/**
 Captures custom events. Application can set extra properties specific to this event via the properties parameter.
 
 @param eventName  name of the event to be tracked.
 @param properties event properties to attach with the given event name.
 */
- (void)trackEvent:(NSString *)eventName properties:(NSDictionary *)properties;


/**
 Tracks the engagement for the provided engagement metric type.
 
 @param metric type of engagement to track i.e.: launch, active,iam,premium,social,action etc.
 */
- (void)trackEngagementMetric:(PushIOEngagementMetrics)metric;


/**-----------------------------------------------------------------------------
 * @name Application Lifecycle (UIApplicationDelegate hooks)
 * -----------------------------------------------------------------------------
 */


/**
 Method to be invoked from the application delegate's `didFinishLaunchingWithOptions:` method.
 
 @param launchOptions contains the application launch information.
 */
- (void)didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;


/**
 Method to be invoked from the application delegate's `didReceiveRemoteNotification:` method.
 
 @param userInfo contains the remote notification information.
 */
- (void)didReceiveRemoteNotification:(NSDictionary *)userInfo;


/**
 Method to be invoked from application delegate's `didRegisterForRemoteNotificationsWithDeviceToken:` method.

 @param deviceToken contains value of devicetoken data.
 */
- (void) didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;


/**
 Method to be invoked from the application delegate's `didFailToRegisterForRemoteNotificationsWithError:` method.
 
 @param error contains the error details occur while try to register with APNS.
 */
- (void)didFailToRegisterForRemoteNotificationsWithError:(NSError *)error;


/**
 Method meant to be invoked from the application delegate's `application:openURL:sourceApplication:annotation:` method.
 
 @param URL               URL scheme with which application is invoked.
 @param sourceApplication source application name.
 @param annotation        annotation.
 
 @return TRUE if URL is processed successfully, FALSE otherwise.
 */
- (BOOL)openURL:(NSURL *)URL sourceApplication:(NSString *)sourceApplication annotation:(id)annotation;


/**
 Method meant to be invoked from the application delegate's `didReceiveRemoteNotification:fetchCompletionResult:fetchCompletionHandler:`
 
 @param userInfo    remote notification information.
 @param fetchResult fetchResult.
 @param handler     need to be called to let iOS know that remote notification processed successfully.
 */
- (void)didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionResult:(UIBackgroundFetchResult)fetchResult fetchCompletionHandler:(void (^)(UIBackgroundFetchResult result))handler;


/**
 Method meant to be invoked from the application delegate's `handleActionWithIdentifier: forRemoteNotification: completionHandler:`. When the PushIOManager version is called, the userInfo push dictionary will be processed, an engagement will be triggered, and the completion handler called.
 
 @param identifier        identifier.
 @param userInfo          remote notification information.
 @param completionHandler completionHandler.
 */
- (void)handleActionWithIdentifier:(NSString *)identifier
             forRemoteNotification:(NSDictionary *)userInfo
                 completionHandler:(void (^)(void))completionHandler;



/**-----------------------------------------------------------------------------
 * @name Notification Preferences
 * -----------------------------------------------------------------------------
 */


/**
 Declares a preference. A preference is not stored until a value has been assigned by a setter method.
 @see setBoolPreference:forKey:
 @see setNumberPreference:forKey:
 @see setStringPreference:forKey:
 
 @param key   preference unique identifier.
 @param label human readable preference detail.
 @param type  preference type.
 @param error placeholder to populate the error code/reason if preference declare fail.
 */
- (void)declarePreference:(NSString *)key label:(NSString *)label type:(PIOPreferenceType)type error:(NSError **)error;


/**
 Assigns a boolean value to a previously declared preference.
 
 @param value boolean preference value to assign.
 @param key   unique identifier of preference.
 
 @return TRUE if boolean preference value assigned, FALSE otherwise.
 */
- (BOOL)setBoolPreference:(BOOL)value forKey:(NSString *)key;


/**
 Assigns a numeric value to a previously declared preference.
 
 @param value numeric preference value to assign.
 @param key   unique identifier of preference.
 
 @return TRUE if numeric preference value assigned, FALSE otherwise.
 */
- (BOOL)setNumberPreference:(NSNumber *)value forKey:(NSString *)key;


/**
 Assigns a string value to a previously declared preference.
 
 @param value string preference value to assign.
 @param key   unique identifier of preference.
 
 @return TRUE if string preference value assigned, FALSE otherwise.
 */
- (BOOL)setStringPreference:(NSString *)value forKey:(NSString *)key;


/**
 Retrieve a preference from local persistence storage.
 
 @param key unique identifier of preference.
 
 @return PIOPreference instance if preference is found for the key, NULL otherwise.
 */
- (PIOPreference *)getPreference:(NSString *)key;


/**
 Retrieves all preferences stored.
 
 @return list of instance of PIOPreference found in persistence storage. nil if no preference found.
 */
- (NSArray *)getPreferences;


/**
 Remove a preference identified by provided key. Preferences must be redeclared before assigning again.
 
 @param key   unique identifier of preference.
 @param error placeholder to populate the error code/reason if removePreference fail.
 */
- (void)removePreference:(NSString *)key error:(NSError **)error;


/**
 Removes all preferences. Preferences must be redeclared before assigning again.
 */
- (void)clearAllPreferences;


/**-----------------------------------------------------------------------------
 * @name UserID Handlers
 * -----------------------------------------------------------------------------
 */

/** Contains verifiedUserID.
 *
 */
@property(nonatomic, strong) NSString *verifiedUserID;

/**
 An optional UserID can be set to target individual users for push notifications, sent along with push registration.
 
 @param userID string value contains the userID to store and sync.
 */
- (void)registerUserID:(NSString *)userID;


/**
 @deprecated This method is deprecated starting from version 6.32.0
 @note Please use @code registerUserID: @endcode by passing nil or empty string to unregister userID instead.
 
 Removes registered userID and re-registers with PushIO server.
 */
- (void)unregisterUserID __attribute__((deprecated));


/**
 @deprecated This method is deprecated starting from version 6.32.0
 @note Please use @code getUserID @endcode to get the userID and match with your version of userID.
 
 Check if a given userID is registered with SDK.
 
 @param userID string value contains the userID to check against already registered one.
 
 @return TRUE if given userID match with already registered userID, FALSE otherwise.
 */
- (BOOL)isRegisteredForUserID:(NSString *)userID __attribute__((deprecated));


/**
 Returns The current registered userID.
 
 @return string value of registered userID. nil of no userID registered.
 */
- (NSString *)getUserID;

/**
 @deprecated This method is deprecated starting from version 6.32.0
 @note Please use @code getUserID @endcode instead.
 
 Returns The current registered userID.
 
 @return string value of registered userID. nil of no userID registered.
 */
- (NSString *)registeredUserID __attribute__((deprecated));


/**-----------------------------------------------------------------------------
 * @name Categories Handlers
 * -----------------------------------------------------------------------------
 */


/**
 Register a list of categories for this device with Push IO. Categories let application to opt  into specific groups. Any category not present in the array will be unregistered if already registered with the PushIO server.
 
 @param categories list of categories (string values) to get registered.
 */
- (void)registerCategories:(NSArray *)categories;


/**
 Registers a single category, leaving any other categories still registered.
 
 @param category string value of category to register with PushIO server.
 */
- (void)registerCategory:(NSString *)category;


/**
 Unregister a single category, leaving all other categories in place.
 
 @param category string value of category to unregister from PushIO server.
 */
- (void)unregisterCategory:(NSString *)category;


/**
 Unregisters a list of categories, leaving any categories not in the passed in array still registered.
 
 @param categories list of categories to unregister from PushIO server.
 */
- (void)unregisterCategories:(NSArray *)categories;


/**
 Unregister all categories for this device from Push IO.
 */
- (void)unregisterAllCategories;


/**
 Check if given category already registered with PushIO SDK.
 
 @param category string value of category to check if already registered.
 
 @return TRUE if given category is already registered, FALSE otherwise.
 */
- (BOOL)isRegisteredForCategory:(NSString *)category;


/**
 Returns all registered categories.
 
 @return array of category(strings) if there are one or more categories registered, NULL otherwise.
 */
- (NSArray *)allRegisteredCategories;


/**
 @warning This override will make it inconsistent IAM and RichPush. Don't use this until consequences are fully analyzed.
 */
@property (nonatomic, strong) NSString *overrideURLScheme;

      
/**
 @unavailable This method is deprecated starting from version 6.32.0
 @note Please use @code configuewithAPIKey: @endcode instead.
 
 Override the configured APIKey.
 
 @param overridePushIOAPIKey string value of new API Key.
 */
- (void)setOverridePushIOAPIKey:(NSString *)overridePushIOAPIKey __attribute__((deprecated));


/**
 @unavailable This method is deprecated starting from version 6.32.0
 @note Please use @code configuewithAPIKey: @endcode instead.
 
 Override the configured AccountToken.
 
 @param overrideAccountToken string value of new Account Token.
 */
- (void)setOverrideAccountToken:(NSString *)overrideAccountToken __attribute__((deprecated));


/**
 A unique ID used by SDK to configure the application.
 
 @note Uses CFUUID internally to generate the deviceID.
 
 @return non-null string value of device ID generated and used by SDK.
 */
- (NSString *)getDeviceID;


/**
 @deprecated This method is deprecated starting from version 6.32.0
 @note Please use @code getDeviceID @endcode instead.
 
 A unique ID used by SDK to configure the application.
 
 @return non-null string value of device ID generated and used by SDK.
 */
- (NSString *)pushIOUUID __attribute__((deprecated));


/**
 Configured API key.
 
 @return string value of configured APIKey. nil if no apikey configured.
 */
- (NSString *)getAPIKey;


/**
 Configured AccountToken value.
 
 @return string value of configured AccountToken. nil if no AccountToken configured.
 */
- (NSString *)getAccountToken;

/**
 @deprecated This method is deprecated starting from version 6.32.0
 @note Please use @code getAPIKey @endcode instead.
 
 Configured API key.
 
 @return string value of configured APIKey. nil if no apikey configured.
 */
- (NSString *)pushIOAPIKey __attribute__((deprecated));


/**
 @deprecated This method is deprecated starting from version 6.32.0
 @note Please use @code getAccountToken @endcode instead.
 
 Configured AccountToken value.
 
 @return string value of configured AccountToken. nil if no AccountToken configured.
 */
- (NSString *)pushIOAccountToken __attribute__((deprecated));

/**
 Returns the version of this framework in use.

 @return framework version.
 */
- (NSString *) frameworkVersion;


//Metadata handler

/**
 Gives the PushIO SDK a handler to call back when extended metadata is present in the push.
 See the description of the PushIOPushMetaHandler protocol for effects if not set or not implementing specific methods.
 */
@property (nonatomic, assign) id <PushIOPushMetaHandler> pushMetaHandlerDelegate;


/**
 If there was a URL present in the last push, then this returns the URL sent. If the URL had been shortened by the PushIO servers, this will return the expanded URL string.
 */
@property (nonatomic, readonly) NSString *lastPushURLString;

#if defined(__IPHONE_10_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_10_0


/**-----------------------------------------------------------------------------
 * @name iOS10 Notification Methods
 * -----------------------------------------------------------------------------
 */


/**
 Asks user permissions for provided notifications types i.e.: Sound/Badge/Alert types.
 If readyForRegistrationCompHandler is not set, then provided completionHandler is assigned to it, to let application have access when SDK receives deviceToken.
 
 @param authOptions Notification auth types i.e.: Sound/Badge/Alert
 @param categories Contains the notification categories definitions.
 @param completionHandler callback with response for notification permission prompt.
 
 */
-(void) registerForNotificationAuthorizations:(UNAuthorizationOptions)authOptions categories:(NSArray *)categories completionHandler:(PIOCompletionHandler)completionHandler;


/**
 Must be called by the UNUserNotificationDelegate's
 userNotificationCenter:didReceiveNotificationResponse:withCompletionHandler.

 @param center            The notification center.
 @param response          The notification response.
 @param completionHandler A completion handler.
 */
-(void) userNotificationCenter:(UNUserNotificationCenter *)center
didReceiveNotificationResponse:(UNNotificationResponse *)response
         withCompletionHandler:(void(^)())completionHandler;



/**
 Must be called by UNUserNotificationDelegate's
 userNotificationCenter:willPresentNotification:withCompletionHandler.

 @param center            The notification center.
 @param notification      The notification response.
 @param completionHandler A completion handler.
 */
-(void) userNotificationCenter:(UNUserNotificationCenter *)center
       willPresentNotification:(UNNotification *)notification
         withCompletionHandler:(void (^)(UNNotificationPresentationOptions options))completionHandler;

#else

/**
 Asks user to provide the permissions for provided notifications types i.e.: Sound/Badge/Alert types.
 If readyForRegistrationCompHandler is not set, then provided completionHandler is assigned to it, to let application have access when SDK receives deviceToken.
 
 @param notificationType Notification types i.e.: Sound/Badge/Alert
 @param categories Categories dictionary containing categories and action details.
 @param completionHandler callback with response for notification permission prompt.
 
 */
-(void) registerForNotificationTypes:(UIUserNotificationType)notificationType categories:(NSArray *)categories completionHandler:(PIOCompletionHandler)completionHandler;


/**
 Method to be invoked from the application delegate's `didRegisterUserNotificationSettings:` method.
 
 @param notificationSettings updated notification settings
 */
-(void) didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings;

#endif


//MARK: Message Center Methods

/**
 Fetch the list of Message Center messages for given MessageCenter name.
 
 @param messageCenter     Name of MessageCenter to fetch the list of messages.
 @param completionHandler Callback to notify when operation complete.
 */
-(void) fetchMessagesForMessageCenter:(NSString *)messageCenter CompletionHandler:(PIOMessageCenterCompletionHandler)completionHandler;

@end
