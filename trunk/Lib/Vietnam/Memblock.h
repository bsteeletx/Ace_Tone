#ifndef _MEMBLOCK_H_
#define _MEMBLOCK_H_

#include "Image.h"

class Image;

class Memblock
{
public:
	Memblock(void);
	~Memblock(void);
	Memblock(Image Generator);
	Memblock(unsigned int size);
	
	void Delete();

	int GetByte(unsigned int offset);
	bool GetExists(void);
	float GetFloat(unsigned int offset);
	unsigned int GetID(void);
	int GetInt(unsigned int offset);
	short GetShort(unsigned int offset);
	unsigned int GetSize(void);

	void SetByte(unsigned int offset, int value);
	void SetFloat(unsigned int offset, float value);
	void SetInt(unsigned int offset, int value);
	void SetShort(unsigned int offset, short value);

private:
	unsigned int _memBlockID;
};

#endif