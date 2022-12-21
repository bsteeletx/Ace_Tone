#include "3D.h"
#include "agk.h"

ThreeD::ThreeD(unsigned int depth)
{
	agk::SetGlobal3DDepth(depth);
}


ThreeD::~ThreeD(void)
{
}
