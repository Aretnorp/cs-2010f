#ifndef __ROTATION_LIMITS_H_
#define __ROTATION_LIMITS_H_
class RotationLimits
{
public:
	RotationLimits(void);
	~RotationLimits(void);
	int minX;
	int minY;
	int minZ;
	int maxX;
	int maxY;
	int maxZ;
};
#endif

