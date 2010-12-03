#include "RotationLimits.h"

/*-----------------------------------------------------------------------------
*  RotationLimits
*  Create a new RotationLimits object with min and max set to 0
*-----------------------------------------------------------------------------*/
RotationLimits::RotationLimits(void)
{
	this->minX = this->minY = this->minZ = 0;
	this->maxX = this->maxY = this->maxZ = 0;
}

/*-----------------------------------------------------------------------------
*  ~RotationLimits
*  Destroy a RotationLimits
*-----------------------------------------------------------------------------*/
RotationLimits::~RotationLimits(void)
{
}
