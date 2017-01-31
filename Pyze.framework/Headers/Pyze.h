
#import <Foundation/Foundation.h>
#import "PyzeEvent.h"

//! Project version number for Pyze.
FOUNDATION_EXPORT double PyzeVersionNumber;

//! Project version string for Pyze.
FOUNDATION_EXPORT const unsigned char PyzeVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <Pyze/PublicHeader.h>



/**
 *  PyzeLogLevel
 *  Log level of the SDK.
 *  Default is Minimal Logs
 */
typedef NS_ENUM(NSInteger, PyzeLogLevel) {
    /**
     *  Log Minimal
     *
     *  How to use:
     *
     *    [Pyze logThrottling:PyzelogLevelMinimal];
     */
    PyzelogLevelMinimal = 0,
    /**
     *  Log Mininmal + warnings
     *
     *  How to use:
     *
     *    [Pyze logThrottling:PyzelogLevelWarnings];
     */
    PyzelogLevelWarnings = 1,
    /**
     * Log Mininmal + warnings + errors
     *
     * How to use:
     *
     *    [Pyze logThrottling:PyzelogLevelErrors];
     */
    PyzelogLevelErrors = 2,
    /**
     * Log all messages
     *
     * How to use:
     *
     *    [Pyze logThrottling:PyzelogLevelAll];
     */
    PyzelogLevelAll = 3
};

/**
 *  PyzeAspectRatio
 *
 *  It will be used to display InApp Messages screen based on the aspect ratio of the screen on which In App messages will be presented.
 */
typedef NS_ENUM(NSInteger, PyzeAspectRatio) {
    /**
     *  Full size screen. InApp Messages screen will cover the screen on which In App messages will be presented.
     */
    PyzeAspectRatioFullSize,
    /**
     *  3/4 of the screen. InApp Messages screen will cover 75% of the screen on which In App messages will be presented.
     */
    PyzeAspectRatioThreeQuarterSize,
    /**
     *  1/2 of the screen. InApp Messages screen will cover 50% of the screen on which In App messages will be presented.
     */
    PyzeAspectRatioHalfSize
};

/**
 *  PyzeInAppMessageType
 *
 *  This enum will be used to display New InApp messages [Unread messages] or Previous messages [Read messages] or both.
 *
 */
typedef NS_ENUM(NSInteger, PyzeInAppMessageType) {
    /**
     *  New InApp messages [Unread messages including unfetched]
     */
    PyzeInAppTypeUnread,
    /**
     *  Previous messages [Read messages]
     */
    PyzeInAppTypeRead,
    /**
     *  New InApp messages [Unread messages] & Previous messages [Read messages]
     */
    PyzeInAppTypeAll
};


/**
 *  Pyze deep link status enumeration, useful to determine whether deeplink provided, successful or failed.
 *
 *  - Since: v3.0.5
 */
typedef NS_ENUM(NSInteger, PyzeDeepLinkStatus) {
    /**
     *  Deeplink not provided while creating the in-app
     */
    PyzeDeepLinkNotProvided = 0,
    /**
     *  Deeplink successfully called. For Example: (http://pyze.com or yelp://search?term=burritos where yelp application is installed on the device)
     */
    PyzeDeepLinkCallSuccessful,
    /**
     *  Invalid or deeplink not found. For Example: (mispelt htp://pyze.com or yelp://search?term=burritos where yelp application is not installed on the device)
     */
    PyzeDeepLinkCallFailed
};


#pragma mark - Pyze
/**
 * Pyze main class
 *
 * This is the main class for the Pyze iOS SDK. Use method initializeWithKey: to initialize the Library.
 * For troubleshooting during development and in debug mode, you can throttle the logging level using method
 * debugLogThrottling:
 * In the release mode or deployment the SDK will log minimally.
 *
 * Please visit [Pyze Developer Center](http://docs.pyze.com) for more information.
 *
 * You will need an app-specific key "Pyze App Key" from: [growth.pyze.com](https://growth.pyze.com/)
 *
 */

@interface Pyze : NSObject


/// @name Initializing Pyze

/**
 *  Initializes the Pyze library. Call this method in the app delegate's method
 *  application:willFinishLaunchingWithOptions. [Get Pyze App Key from growth.pyze.com](http://pyze.com/get-Pyze-App-Key.html)
 *
 *  Usage:
 *
 *      [Pyze initialize:@"Pyze App Key obtained from growth.pyze.com"];
 *
 *  @param pyzeAppKey The app-specific key obtained from [growth.pyze.com](http://pyze.com/get-Pyze-App-Key.html)
 *  @warning *Important:* Get an app-specific key from [growth.pyze.com](http://pyze.com/get-Pyze-App-Key.html)
 *
 *  - Since: v3.0.5
 *
 */
+ (void) initialize:(nonnull NSString *) pyzeAppKey;

/**
 *  Initializes the Pyze library and specify the log throttling level. Call this method in the app delegate's method
 *  application:willFinishLaunchingWithOptions. [Get Pyze App Key from growth.pyze.com](http://pyze.com/get-Pyze-App-Key.html)
 *
 *  Usage:
 *
 *      [Pyze initialize:@"Pyze App Key obtained from growth.pyze.com"   withLogThrottling: PyzelogLevelAll];
 *
 *  @param pyzeAppKey The app-specific key obtained from [growth.pyze.com](http://pyze.com/get-Pyze-App-Key.html)
 *  @param logLevel Log level you would wish to see in the console.
 *  @warning *Important:* Get an app-specific key from [growth.pyze.com](http://pyze.com/get-Pyze-App-Key.html)
 *
 *  - Since: v3.0.5 (added for consistency with Android and Unity agents)
 *
 */
+ (void) initialize:(nonnull NSString *)pyzeAppKey withLogThrottling: (PyzeLogLevel) logLevel;


/**
 *  Log throttling level can be changed anytime in the app
 *
 *  How to use:
 *
 *    [Pyze logThrottling:PyzelogLevelMinimal];
 *
 *  or
 *
 *    [Pyze logThrottling:PyzelogLevelErrors];
 *
 *  @param logLevel Log level you would wish to see in the console.
 *
 *  - Since: v3.0.5
 *
 */
+(void) logThrottling:(PyzeLogLevel) logLevel;


/// @name  Create Timer Reference to use in Timed Custom Events using PyzeCustomEvent class

/**
 *  Pyze Timer Reference is a time interval since a Pyze internal reference time in seconds with millisecond precision e.g. 6.789 seconds (or 6789 milliseconds)
 *
 *  It is used to time tasks and report in events.
 *
 *  usage:
 *
 *     //Start timing
 *     double referenceFileUploadStart = [Pyze timerReference];
 *     ...
 *     ...
 *     //time and send elapsedSeconds
 *     [PyzeCustomEvent postWithEventName:@“File Uploaded”
 *                     withTimerReference:referenceFileUploadStart];
 *
 */
+(double) timerReference;

/**
 *  Hash function can be used to convert any NSString to an hashed equivalent.
 *  The generated string is suffixed with two hash characters ##
 *  This function is useful to avoid collecting any information that may be private or sensitive.
 *
 *  @param stringToHash         String to Hash
 *
 *  - Since: v3.0.5
 */
+ (nonnull NSString *)hash:(nonnull NSString *)stringToHash;


@end
