#ifndef __TORSO_H_
#define __TORSO_H_
#include "Shape.h"

class Torso :
	public Shape
{
private:
	int width;
	int height;
	int index;
public:
	Torso(int width, int height, RotationLimits* = new RotationLimits());
	~Torso(void);

	void Draw(void);

	void MoveToRightArm(void);
	void MoveToLeftArm(void);

	void MoveToRightLeg(void);
	void MoveToLeftLeg(void);

	void MoveToHead();
};
#endif

