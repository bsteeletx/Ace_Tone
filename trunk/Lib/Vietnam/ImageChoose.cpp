#include "ImageChoose.h"
#include "agk.h"

Choose::Choose()
: Image()
{
	if (!_ShowScreen())
	{
		this->~Choose();
		return;
	}

	while (_IsChoosing());

	_imageNumber = _Get();

	if (_imageNumber == 0)
	{
		this->~Choose();
		return;
	}
}

Choose::~Choose()
{

}

unsigned short Choose::_Get()
{
	return agk::GetCapturedImage();
}

bool Choose::_IsChoosing()
{
	return (bool)agk::IsCapturingImage();
}

bool Choose::_ShowScreen()
{
	return (bool)agk::ShowChooseImageScreen();
}