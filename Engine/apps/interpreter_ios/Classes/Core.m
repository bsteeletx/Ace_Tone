// Common Includes
#import "core.h"
#import "EAGLView.h"

// App specific include for Core (so core can be distributed between apps without editing inside it) (iPhone4)
#define DEVICE_WIDTH 640
#define DEVICE_HEIGHT 960
#include "CoreForApp.h"

#include "MediaPlayer/MediaPlayer.h"

// Platform specific
void Output ( char const* pdasds )
{
}

using namespace AGK;
@implementation iphone_appAppDelegate
@synthesize window;
@synthesize viewController;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	// Determine name of app
	if ( AppInitCode()==0 )
		return NO;
	
	// Platform specific iOS method of changing size of device resolution (before app starts)
	// and method of changing window title and window/fullscreen
	// NOT RELEVANT TO IOS PLATFORM

	// Tell the UIDevice to send notifications when the orientation changes
	[[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
	[[NSNotificationCenter defaultCenter] addObserver:self 
											 selector:@selector(orientationChanged:) 
												 name:@"UIDeviceOrientationDidChangeNotification" 
											   object:nil];
	
	//[ window addSubview: viewController.view ];
    [window setRootViewController:viewController];
	[ window makeKeyAndVisible ];
	
	// call app begin
	App.Begin();
	[viewController setActive];
    
    
	
	// success
    return YES;
}

- (NSUInteger)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window 
{
    return UIInterfaceOrientationMaskAll;
}

- (void)application:(UIApplication*)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData*)deviceToken
{
    const unsigned char *dataBuffer = (const unsigned char *)[deviceToken bytes];
    
    NSUInteger          dataLength  = [deviceToken length];
    NSMutableString     *hexString  = [NSMutableString stringWithCapacity:(dataLength * 2)];
    
    for (int i = 0; i < dataLength; ++i)
        [hexString appendString:[NSString stringWithFormat:@"%02x", (unsigned int)dataBuffer[i]]];
    
    agk::PNToken( [hexString UTF8String] );
}

- (void)application:(UIApplication*)application didFailToRegisterForRemoteNotificationsWithError:(NSError*)error
{
    agk::PNToken( "Error" );
	NSLog(@"Failed to get token, error: %@", error);
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
	agk::Resumed();
}

- (void)applicationWillResignActive:(UIApplication *)application
{
	[viewController setInactive];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
	[viewController setActive];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
	// end the app
	[viewController setInactive];
	App.End();
}

- (void)dealloc
{
    [viewController release];
    [window release];
    [super dealloc];
}

- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag
{
	agk::HandleMusicEvents( NULL );
}

- ( void ) accelerometer: ( UIAccelerometer* ) accelerometer didAccelerate: ( UIAcceleration* ) acceleration
{
	agk::Accelerometer( acceleration.x, -acceleration.y, -acceleration.z );
}

- (void)orientationChanged:(NSNotification *)notification
{
	UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
	float angle = 0;
	
	int mode = 1;
	switch( orientation )
	{
		case UIDeviceOrientationPortrait: mode=1; break; 
		case UIDeviceOrientationPortraitUpsideDown: mode=2; angle = 3.1415927f; break; 
		case UIDeviceOrientationLandscapeLeft: mode=3; angle = 1.5707963f; break;
		case UIDeviceOrientationLandscapeRight: mode=4; angle = -1.5707963f; break; 
		default: return;
	}
	
	agk::OrientationChanged( mode );
}

@end


@implementation iphone_appAppDelegate ( Facebook )

- ( BOOL ) application: ( UIApplication* ) application handleOpenURL: ( NSURL* ) url 
{
    // called by Facebook when returning back to our application after signing in,
    // this version is called by OS 4.2 and previous
    
    return agk::FacebookHandleOpenURL(url) > 0;
}

- ( BOOL ) application: ( UIApplication* ) application openURL: ( NSURL* ) url sourceApplication: ( NSString* ) sourceApplication annotation: ( id ) annotation 
{
    // same as above but for OS 4.3 and later
    
    return agk::FacebookHandleOpenURL(url) > 0;
}

- ( void ) application: ( UIApplication* ) application didReceiveLocalNotification: ( UILocalNotification* ) notification 
{
    // called when the app receives a local notification
    
    // extract the data we need
    NSString* nsName    = [ notification.userInfo objectForKey: @"Key 1" ];
    char*     utfString = ( char* ) [ nsName UTF8String ];
    
    agk::FacebookReceivedNotification( utfString );
    
    // reset the icon badge to 0
	application.applicationIconBadgeNumber = 0;
}

@end

