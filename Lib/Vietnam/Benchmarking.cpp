#include "Benchmarking.h"
#include "agk.h"

Benchmarking::Benchmarking()
{
}

Benchmarking::~Benchmarking()
{
}

//Returns the number of seconds and fractions of seconds spent setting up the world ready for drawing. 
//This includes calculating what is visible, transforming sprites into their screen positions and sending vertices to the GPU.
float Benchmarking::GetDrawingSetupTime(void)
{
	return agk::GetDrawingSetupTime();
}

//Returns the time spent swapping the backbuffer and (if necessary) waiting for the GPU to catch up ready for the next frame.
float Benchmarking::GetDrawingTime()
{
	return agk::GetDrawingTime();
}

//Returns the number of images currently loaded into the app
unsigned short Benchmarking::GetLoadedImages()
{
	return agk::GetLoadedImages();
}

/**************************
** Returns the number of sprites that are being managed by the internal sprite manager. 
** It is responsible for updating sprite animation and calculating which sprites are visible and need to be sent for drawing. 
** It also sorts the sprites when necessary for correct transparency drawing.
** As long as not too many sprites are sent for drawing the sprite manager should be able to handle several hundred sprites.
*///////////////////////////
unsigned short Benchmarking::GetManagedSpriteCount()
{
	return agk::GetManagedSpriteCount();
}

/******************************
** Returns the number of OpenGL draw calls used to draw all managed sprites. 
** Generally the lower this number the better the performance. 
** AGK attempts to batch sprites into as few draw calls as possible, it does this by looking for sprites with the same texture and drawing them at the same time. 
** This can be improved by using SetSortTextures to turn on texture sorting to put sprites with the same texture next to each other in the draw queue
*/////////////////////////////
unsigned short Benchmarking::GetManagedSpriteDrawCalls()
{
	return agk::GetManagedSpriteDrawCalls();
}

/********************************
** Returns the number of sprites that were actually sent for rendering to the GPU last frame, the more that get drawn the slower the app will run.
*/////////////////////////////////
unsigned short Benchmarking::GetManagedSpriteDrawnCount()
{
	return agk::GetManagedSpriteDrawnCount();
}

/**********************************
** Returns the number of sprites that the internal sprite manager had to sort into their correct positions since the last frame. 
** Sprites only need resorting if they change depth or texture during the current frame. 
** You can control how mush sorting is done with the commands SetSortTextures, SetSortDepth, and SetSortTransparentDepth.
*////////////////////////////////////
unsigned short Benchmarking::GetManagedSpriteSortedCount()
{
	return agk::GetManagedSpriteSortedCount();
}

/**********************************
** Returns the number of individual particles that were drawn last frame using a quad method. 
** The higher this number the more work the engine is doing handling particles.
*//////////////////////////////////
unsigned short Benchmarking::GetParticleDrawnQuadCount()
{
	return agk::GetParticleDrawnQuadCount();
}

/***********************************
** Returns the number of seconds and fractions of seconds spent updating the physics simulation.
*////////////////////////////////////
float Benchmarking::GetPhysicsTime()
{
	return agk::GetPhysicsTime();
}

/***********************************
** Returns an estimate of the number of pixels that were drawn to the screen last frame. 
** Generally the lower this value the better the performance. 
** The number of pixels drawn can be greater than the number of pixels in the screen since overlapping sprites might draw the same pixel twice
*////////////////////////////////////
unsigned int Benchmarking::GetPixelsDrawn()
{
	return agk::GetPixelsDrawn();
}

/***********************************
** Returns the filename of the specified unassigned image
** Unassgined image is a value from 1 to value gotten from GetUnassignedImages
*/////////////////////////////////
Text Benchmarking::GetUnassignedImageFileName(unsigned int unassignedImageIndex)
{
	return Text(agk::GetUnassignedImageFileName(unassignedImageIndex));
}

/***********************************
** Returns the number of images currently loaded into the app but are not assigned to a sprite or text object. 
** This is useful for debugging to check you have deleted all unused images when switching from a menu to a level, or from one level to another.
*///////////////////////////////////
unsigned short Benchmarking::GetUnassignedImages()
{
	return agk::GetUnassignedImages();
}

/***********************************
** Returns the number of seconds and fractions of seconds spent updating everything in the world except physics. 
** This includes sprite animation, emulating input, and handling sounds.
*/////////////////////////////////
float Benchmarking::GetUpdateTime()
{
	return agk::GetUpdateTime();
}