#ifndef __PERSON_H_
#define __PERSON_H_
#include <vector>
#include "Shape.h"
#include "Torso.h"
#include "Square.h"
#include "Arm.h"
#include "Leg.h"
#include "Head.h"
#include "ShapeContainer.h"

class Person :
	public Shape,
	public ShapeContainer
{
private:
	Torso* torso;
	Arm* leftArm;
	Arm* rightArm;
	Leg* leftLeg;
	Leg* rightLeg;
	Head* head;
public:
	Person(void);
	~Person(void);

	void Draw(void);
};
#endif

