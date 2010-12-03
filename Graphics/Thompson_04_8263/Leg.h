#ifndef __LEG_H_
#define __LEG_H_
#include "Shape.h"
#include "ShapeContainer.h"
#include "Square.h"

class Leg :
	public Shape,
	public ShapeContainer
{
private:
	Square* upperLeg;
	Square* lowerLeg;
	Square* foot;
public:
	Leg(void);
	~Leg(void);
	
	void Draw(void);
    void RotateObject(int x, int y);
};
#endif
