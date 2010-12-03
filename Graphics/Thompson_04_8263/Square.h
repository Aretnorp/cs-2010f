#ifndef __SQUARE_H_
#define __SQUARE_H_
#include "Shape.h"

class Square :
	public Shape
{
private:
	int size;
	int index;
	void GetRotations(void);

public:
	Square(int size, RotationLimits* rot = new RotationLimits());
	~Square(void);

	void Draw();
	void GetJoint();
};
#endif
