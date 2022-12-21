#include "Memblock.h"
#include "agk.h"

Memblock::Memblock(void)
{
	_memBlockID = 0;
}


Memblock::~Memblock(void)
{
}

Memblock::Memblock(unsigned int size)
{
	_memBlockID = agk::CreateMemblock(size);
}

Memblock::Memblock(Image Generator)
{
	_memBlockID = agk::CreateMemblockFromImage(Generator.GetID());
}

void Memblock::Delete()
{
	agk::DeleteMemblock(_memBlockID);
}

int Memblock::GetByte(unsigned int offSet)
{
	return agk::GetMemblockByte(_memBlockID, offSet);
}

bool Memblock::GetExists(void)
{
	if (agk::GetMemblockExists(_memBlockID))
		return true;

	return false;
}

float Memblock::GetFloat(unsigned int offSet)
{
	return agk::GetMemblockFloat(_memBlockID, offSet);
}

unsigned int Memblock::GetID(void)
{
	return _memBlockID;
}

int Memblock::GetInt(unsigned int offSet)
{
	return agk::GetMemblockInt(_memBlockID, offSet);
}

short Memblock::GetShort(unsigned int offSet)
{
	return agk::GetMemblockShort(_memBlockID, offSet);
}

unsigned int Memblock::GetSize(void)
{
	return agk::GetMemblockSize(_memBlockID);
}

void Memblock::SetByte(unsigned int offSet, int value)
{
	agk::SetMemblockByte(_memBlockID, offSet, value);
}

void Memblock::SetFloat(unsigned int offSet, float value)
{
	agk::SetMemblockFloat(_memBlockID, offSet, value);
}

void Memblock::SetInt(unsigned int offSet, int value)
{
	agk::SetMemblockInt(_memBlockID, offSet, value);
}

void Memblock::SetShort(unsigned int offSet, short value)
{
	agk::SetMemblockShort(_memBlockID, offSet, value);
}