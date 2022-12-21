#include "Video.h"
#include "agk.h"

Video::Video(Text VideoFilename)
{
	_error = agk::LoadVideo(VideoFilename.GetCString());
}


Video::~Video(void)
{
}

void Video::Delete()
{
	agk::DeleteVideo();
}

float Video::GetDuration(void)
{
	return agk::GetVideoDuration();
}

short Video::GetError(void)
{
	return _error;
}

float Video::GetHeight(void)
{
	return agk::GetVideoHeight();
}

bool Video::GetPlaying(void)
{
	if(agk::GetVideoPlaying())
		return true;

	return false;
}

float Video::GetPosition(void)
{
	return agk::GetVideoPosition();
}

float Video::GetWidth(void)
{
	return agk::GetVideoWidth();
}

void Video::Pause(void)
{
	agk::PauseVideo();
}
	
void Video::Play(void)
{
	agk::PlayVideo();
}

void Video::SetDimensions(RFTPoint Location, float width, float height)
{
	agk::SetVideoDimensions(Location.GetX(), Location.GetY(), width, height);
}

void Video::SetVolume(float value)
{
	agk::SetVideoVolume(value);
}
	
void Video::Stop(void)
{
	agk::StopVideo();
}