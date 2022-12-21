#include "MagicPointer.h"

MagicPointer::MagicPointer()
: Pointer()
{
	_Emitter = new RFTParticles(GetPosition().GetX(), GetPosition().GetY());
	_Emitter->SetFrequency(100.0f);
	_Emitter->SetAngle(0.0f);
	_Emitter->SetColorInterpolation(true);
	_Emitter->SetDirection(0.0f, 0.0f);
	_Emitter->SetLife(2.0f);
	_Emitter->SetStartZone(RFTPoint(0.0f, 0.0f), RFTPoint(0.0f, 0.0f));
	_Emitter->AddColorKeyFrame(0.0f, Color(255, 255, 255));
	_Emitter->AddColorKeyFrame(1.0f, Color(192, 192, 255, 192));
	_Emitter->AddColorKeyFrame(1.9f, Color(128, 128, 255, 255));
	_Emitter->AddForce(0.0f, 2.0f, 0.0f, 9.8f);
	_Emitter->SetSize(0.25f);
	_Emitter->SetActive(false);

	//_SlashSound = new Sound("Audio/Slash2.m4a");
}

MagicPointer::~MagicPointer()
{

}

void MagicPointer::Delete()
{
	_Emitter->Delete();
}

void MagicPointer::Update()
{
	_Emitter->Update(0.02f);

	if (GetState())
	{
		if (!_Emitter->GetActive())
			_Emitter->SetActive(true);

		if (_Emitter->GetMaxReached())
		{
			_Emitter->SetMax(-1);
			_Emitter->ResetCount();
		}
		
		_Emitter->SetPosition(GetPosition());
	}
	else
	{
		_Emitter->SetMax(0);
		//_Emitter->SetFrequency(0.0f);
	}
	/*else if (_Emitter->GetActive())
	{
		_Emitter->SetActive(false);
	} */
}