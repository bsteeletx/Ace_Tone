#include "Particles.h"
#include "agk.h"

RFTParticles::RFTParticles(void)
{
	_particleNumber = 0;
}

RFTParticles::~RFTParticles(void)
{
	//if (GetExists())
		//agk::DeleteParticles(_particleNumber);
}

RFTParticles::RFTParticles(float x, float y)
{
	_particleNumber = agk::CreateParticles(x, y);
}

RFTParticles& RFTParticles::operator= (const RFTParticles& newParticle)
{	
	if (this != &newParticle)
	{
		_particleNumber = newParticle._particleNumber;
	}

	return *this;
}

RFTParticles::RFTParticles(unsigned int assignedNumber, float x, float y)
{
	if (assignedNumber != 0)
	{
		agk::CreateParticles(assignedNumber, x, y);
		_particleNumber = assignedNumber;
	}
}

void RFTParticles::AddColorKeyFrame(float time, Color Values)
{
	if (time > 0.0f)
		agk::AddParticlesColorKeyFrame(_particleNumber, time, Values.GetRed(), Values.GetGreen(), Values.GetBlue(), Values.GetAlpha());
}

void RFTParticles::AddForce(float startTime, float endTime, float xAcc, float yAcc)
{
	if (startTime < endTime)
	{
		if (startTime >= 0.0f)
			agk::AddParticlesForce(_particleNumber, startTime, endTime, xAcc, yAcc);
	}
}

void RFTParticles::ClearColors(void)
{
	agk::ClearParticlesColors(_particleNumber);
}

void RFTParticles::ClearForces(void)
{
	agk::ClearParticlesForces(_particleNumber);
}

void RFTParticles::Delete()
{
	agk::DeleteParticles(_particleNumber);
}

void RFTParticles::FixToScreen(bool toScreen)
{
	if (toScreen)
		agk::FixParticlesToScreen(_particleNumber, 1);
	else
		agk::FixParticlesToScreen(_particleNumber, 0);
}

bool RFTParticles::GetActive(void)
{
	if (agk::GetParticlesActive(_particleNumber) == 1)
		return true;
	
	return false;
}

float RFTParticles::GetAngle(void)
{
	return agk::GetParticlesAngle(_particleNumber);
}

float RFTParticles::GetAngleInRad(void)
{
	return agk::GetParticlesAngleRad(_particleNumber);
}

unsigned short RFTParticles::GetDepth(void)
{
	return (unsigned short) agk::GetParticlesDepth(_particleNumber);
}

float RFTParticles::GetDirectionX(void)
{
	return agk::GetParticlesDirectionX(_particleNumber);
}

float RFTParticles::GetDirectionY(void)
{
	return agk::GetParticlesDirectionY(_particleNumber);
}

bool RFTParticles::GetExists(void)
{
	if (agk::GetParticlesExists(_particleNumber) == 1)
		return true;

	return false;
}

float RFTParticles::GetFrequency(void)
{
	return agk::GetParticlesFrequency(_particleNumber);
}

float RFTParticles::GetLife(void)
{
	return agk::GetParticlesLife(_particleNumber);
}

bool RFTParticles::GetMaxReached(void)
{
	if (agk::GetParticlesMaxReached(_particleNumber) == 1)
		return true;
	
	return false;
}

float RFTParticles::GetSize(void)
{
	return agk::GetParticlesSize(_particleNumber);
}

bool RFTParticles::GetVisible(void)
{
	if (agk::GetParticlesVisible(_particleNumber) == 1)
		return true;

	return false;
}

float RFTParticles::GetX(void)
{
	return agk::GetParticlesX(_particleNumber);
}

float RFTParticles::GetY(void)
{
	return agk::GetParticlesY(_particleNumber);
}

void RFTParticles::ResetCount(void)
{
	agk::ResetParticleCount(_particleNumber);
}

void RFTParticles::SetActive(bool active)
{
	if (active)
		agk::SetParticlesActive(_particleNumber, 1);
	else
		agk::SetParticlesActive(_particleNumber, 0);
}

void RFTParticles::SetAngle(float angle)
{
	agk::SetParticlesAngle(_particleNumber, angle);
}

void RFTParticles::SetAngleInRad(float angleInRad)
{
	agk::SetParticlesAngleRad(_particleNumber, angleInRad);
}

void RFTParticles::SetColorInterpolation(bool smooth)
{
	if (smooth)
		agk::SetParticlesColorInterpolation(_particleNumber, 1);
	else
		agk::SetParticlesColorInterpolation(_particleNumber, 0);
}

void RFTParticles::SetDepth(unsigned short depth)
{
	agk::SetParticlesDepth(_particleNumber, depth);
}

void RFTParticles::SetDirection(float xVelocity, float yVelocity)
{
	agk::SetParticlesDirection(_particleNumber, xVelocity, yVelocity);
}

void RFTParticles::SetFrequency(float freq)
{
	if (freq > 0.0f)
		agk::SetParticlesFrequency(_particleNumber, freq);
}

void RFTParticles::SetImage(Image Object)
{
	agk::SetParticlesImage(_particleNumber, Object.GetID());
}

void RFTParticles::SetLife(float lifespan)
{
	if (lifespan > 0.0f)
		agk::SetParticlesLife(_particleNumber, lifespan);
}

void RFTParticles::SetMax(int maxParticles)
{
	agk::SetParticlesMax(_particleNumber, maxParticles);
}

void RFTParticles::SetPosition(RFTPoint Location)
{
	agk::SetParticlesPosition(_particleNumber, Location.GetX(), Location.GetY());
}

void RFTParticles::SetSize(float size)
{
	if(size > 0.0f)
		agk::SetParticlesSize(_particleNumber, size);
}

void RFTParticles::SetStartZone(RFTPoint TopLeft, RFTPoint BottomRight)
{
	agk::SetParticlesStartZone(_particleNumber, TopLeft.GetX(), TopLeft.GetY(), BottomRight.GetX(), BottomRight.GetY());
}

void RFTParticles::SetVelocityRange(float minVelocity, float maxVelocity)
{
	agk::SetParticlesVelocityRange(_particleNumber, minVelocity, maxVelocity);
}

void RFTParticles::SetVisible(bool visible)
{
	if (visible)
		agk::SetParticlesVisible(_particleNumber, 1);
	else
		agk::SetParticlesVisible(_particleNumber, 0);
}

void RFTParticles::Update(float updateSpeed)
{
	if (updateSpeed > 0.0f)
		agk::UpdateParticles(_particleNumber, updateSpeed);
}