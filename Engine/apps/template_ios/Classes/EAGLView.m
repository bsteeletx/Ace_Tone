


#import <QuartzCore/QuartzCore.h>

#import "EAGLView.h"
#include "agk.h"

using namespace AGK;

@implementation EAGLView


// You must implement this method
+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

//The EAGL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:.
- (id)initWithCoder:(NSCoder*)coder
{    
    self = [super initWithCoder:coder];
    return self;
}

@end

@implementation EAGLView ( input )

- ( void ) touchesBegan: ( NSSet* ) touches withEvent: ( UIEvent* ) event
{
	// this function will be activated whenever a touch even begins
	
	for ( UITouch *pTouch in touches )
	{
		CGPoint location = [ pTouch locationInView: self ];
		//NSLog( @"Touch Pressed ID: %p, X: %f, Y: %f", pTouch, location.x, location.y );
		agk::TouchPressed( (UINT) pTouch, location.x, location.y );
	}	
}

- ( void ) touchesMoved: ( NSSet* ) touches withEvent: ( UIEvent* ) event
{
	for ( UITouch *pTouch in touches )
	{
		CGPoint location = [ pTouch locationInView: self ];
		//NSLog( @"Touch Moved ID: %p, X: %f, Y: %f", pTouch, location.x, location.y );
		agk::TouchMoved( (UINT) pTouch, location.x, location.y );
	}
}

- ( void ) touchesEnded: ( NSSet* ) touches withEvent: ( UIEvent* )event
{
	for ( UITouch *pTouch in touches )
	{
		CGPoint location = [ pTouch locationInView: self ];
		//NSLog( @"Touch Released ID: %p, X: %f, Y: %f", pTouch, location.x, location.y );
		agk::TouchReleased( (UINT) pTouch, location.x, location.y );
	}
}

- ( void ) touchesCancelled: ( NSSet* ) touches withEvent: ( UIEvent* )event
{
	for ( UITouch *pTouch in touches )
	{
		CGPoint location = [ pTouch locationInView: self ];
		//NSLog( @"Touch Cancelled ID: %p, X: %f, Y: %f", pTouch, location.x, location.y );
		agk::TouchReleased( (UINT) pTouch, location.x, location.y );
	}
}

@end
