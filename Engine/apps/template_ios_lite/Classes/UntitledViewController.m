//
//  UntitledViewController.m
//  Untitled
//
//  Created by Paul Johnston on 02/12/2010.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

#import "UntitledViewController.h"
#include "AGK.h"
#include "template.h"

using namespace AGK;

// Uniform index.
enum {
    UNIFORM_TRANSLATE,
    NUM_UNIFORMS
};
GLint uniforms[NUM_UNIFORMS];

// Attribute index.
enum {
    ATTRIB_VERTEX,
    ATTRIB_COLOR,
    NUM_ATTRIBUTES
};

BOOL g_bDisplayLinkReady = FALSE;

@interface UntitledViewController ()
@property (nonatomic, retain) EAGLContext *context;
@end

@implementation UntitledViewController

@synthesize context;

- (void)didReceiveMemoryWarning
{
	// doesn't recognise memory pool?
	//NSLog( @"Received memory warning" );
	//extern NSAutoreleasePool *pool;
	//[pool drain];
	[super didReceiveMemoryWarning];
}

- (void)awakeFromNib
{
    CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.view.layer;
	eaglLayer.opaque = TRUE;
	eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
									[NSNumber numberWithBool:TRUE], kEAGLDrawablePropertyRetainedBacking,
									kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat,
									nil];
	
    agk::SetExtraAGKPlayerAssetsMode ( 1 );
	agk::SetResolutionMode(1);
	agk::InitGL( self );
	    
	active = FALSE;
    displayLinkSupported = FALSE;
    frameInterval = 1;
    displayLink = nil;
    syncTimer = nil;
    
    // Use of CADisplayLink requires iOS version 3.1 or greater.
	// The NSTimer object is used as fallback when it isn't available.
    NSString *reqSysVer = @"3.1";
    NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
    if ([currSysVer compare:reqSysVer options:NSNumericSearch] != NSOrderedAscending)
        displayLinkSupported = TRUE;
	
	g_bDisplayLinkReady = TRUE;
    
    agk::SetOrientationAllowed(1,1,1,1);
}

-(BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
#ifdef AGK_LANDSCAPE
    return (interfaceOrientation == UIInterfaceOrientationLandscapeLeft) || (interfaceOrientation == UIInterfaceOrientationLandscapeRight);
#else 
    #ifdef AGK_PORTRAIT
        return (interfaceOrientation == UIInterfaceOrientationPortrait) || (interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown);
    #else
        if ( agk::IsCapturingImage() && ([[UIDevice currentDevice] userInterfaceIdiom] != UIUserInterfaceIdiomPad) )
        {
            return interfaceOrientation == UIInterfaceOrientationPortrait;
        }
        
        switch( interfaceOrientation )
        {
            case UIInterfaceOrientationPortrait: return agk::CanOrientationChange(1) ? YES : NO;
            case UIInterfaceOrientationPortraitUpsideDown: return agk::CanOrientationChange(2) ? YES : NO;
            case UIInterfaceOrientationLandscapeLeft: return agk::CanOrientationChange(4) ? YES : NO;
            case UIInterfaceOrientationLandscapeRight: return agk::CanOrientationChange(3) ? YES : NO;
            default: return NO;
        }
    #endif
#endif
}

-(NSUInteger)supportedInterfaceOrientations
{
#ifdef AGK_LANDSCAPE
    return UIInterfaceOrientationMaskLandscape;
#else
    #ifdef AGK_PORTRAIT
        return UIInterfaceOrientationMaskPortrait | UIInterfaceOrientationMaskPortraitUpsideDown;
    #else
        int result = 0;
        if ( agk::CanOrientationChange(1) ) result |= UIInterfaceOrientationMaskPortrait;
        if ( agk::CanOrientationChange(2) ) result |= UIInterfaceOrientationMaskPortraitUpsideDown;
        if ( agk::CanOrientationChange(3) ) result |= UIInterfaceOrientationMaskLandscapeRight;
        if ( agk::CanOrientationChange(4) ) result |= UIInterfaceOrientationMaskLandscapeLeft;
        return result;
    #endif
#endif
}

-(BOOL)shouldAutoRotate
{
    return YES;
}

-(void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
    //NSLog(@"Orientation Changed");
    agk::UpdatePtr( self );
}

- (void)dealloc
{
    agk::CleanUp();
    
    if (program)
    {
        glDeleteProgram(program);
        program = 0;
    }
    
    // Tear down context.
    if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
    
    [context release];
    
    [super dealloc];
}

- (void)viewWillAppear:(BOOL)animated
{
    [self setActive];
    
    [super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [self setInactive];
    
    [super viewWillDisappear:animated];
}

- (void)viewDidUnload
{
	[super viewDidUnload];
	
    if (program)
    {
        glDeleteProgram(program);
        program = 0;
    }

    // Tear down context.
    if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
	self.context = nil;	
}

- (NSInteger)frameInterval
{
    return frameInterval;
}

- (void)setFrameInterval:(NSInteger)interval
{
    /*
	 Frame interval defines how many display frames must pass between each time the display link fires.
	 The display link will only fire 30 times a second when the frame internal is two on a display that refreshes 60 times a second. The default frame interval setting of one will fire 60 times a second when the display refreshes at 60 times a second. A frame interval setting of less than one results in undefined behavior.
	 */
    if (interval >= 1)
    {
        frameInterval = interval;
        
        if (active)
        {
            [self setInactive];
            [self setActive];
        }
    }
}

- (void)setActive
{
	if ( g_bDisplayLinkReady == FALSE )
        return;
	
    if (!active)
    {
        if (displayLinkSupported)
        {
            // CADisplayLink is API new to iPhone SDK 3.1. Compiling against earlier versions will result in a warning, but can be dismissed
            // if the system version runtime check for CADisplayLink exists in -initWithCoder:. The runtime check ensures this code will
            // not be called in system versions earlier than 3.1.
			
            displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(drawView)];
            [displayLink setFrameInterval:frameInterval];
            [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        }
        else
		{
            syncTimer = [NSTimer scheduledTimerWithTimeInterval:(NSTimeInterval)((1.0 / 60.0) * frameInterval) target:self selector:@selector(drawView:) userInfo:nil repeats:TRUE];
		}
		
        active = TRUE;
    }
}

- (void)setInactive
{
    if (active)
    {
        if (displayLinkSupported)
        {
            [displayLink invalidate];
            displayLink = nil;
        }
        else
        {
            [syncTimer invalidate];
            syncTimer = nil;
        }
		
        active = FALSE;
    }
}


- (void)drawView
{
    App.Loop();
}

@end
