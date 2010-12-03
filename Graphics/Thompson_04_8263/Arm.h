#pragma once
#ifndef __ARM_H_
#define __ARM_H_
#include "Shape.h"
#include "Square.h"
#include "ShapeContainer.h"

class Arm :
	public Shape,
	public ShapeContainer
{
private:
	Square* upperArm;
	Square* lowerArm;
public:
	Arm(bool);
	~Arm(void);

	void Draw(void);
    void RotateObject(int x, int y);
};
#endif

