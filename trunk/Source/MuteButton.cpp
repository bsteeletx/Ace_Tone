#include "MuteButton.h"
#include "Sound.h"
#include "Music.h"

MuteButton::MuteButton()
: VirtualButton()
{}

MuteButton::MuteButton(Image CommonAtlas)
: VirtualButton(RFTPoint(45.0f, 75.0f), 10.0f)
{
	_MuteOffImage = new Sprite(CommonAtlas.GetID(), "Mute Off.png");
	_MuteOnImage = new Sprite(CommonAtlas.GetID(), "Mute On.png");

	_isMuted = false;

	_MuteOffImage->SetVisible(false);
	_MuteOnImage->SetVisible(false);
}

MuteButton::~MuteButton()
{

}

void MuteButton::Init()
{
	SetImageUp(*_MuteOffImage);
	SetImageDown(*_MuteOnImage);
	SetVisible(true);
	/*SetSize(10.0f);
	SetPosition(Point(15.0f, 85.0f));*/
}

void MuteButton::Update()
{
	if (GetPressed())
		_ToggleMute();
}

void MuteButton::_ToggleMute()
{
	Music SoundSystem;
	Sound SoundFXSystem;
	
	_isMuted = !_isMuted;

	if (_isMuted)
	{
		SoundSystem.SetSystemVolume(0);
		SoundFXSystem.SetSystemVolume(0);
		SetImageUp(*_MuteOnImage);
		SetImageDown(*_MuteOffImage);
	}
	else
	{
		SoundSystem.SetSystemVolume(100);
		SoundFXSystem.SetSystemVolume(100);
		SetImageUp(*_MuteOffImage);
		SetImageDown(*_MuteOnImage);
	}
}