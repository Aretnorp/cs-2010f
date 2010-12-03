#ifndef __SHAPE_H_
#define __SHAPE_H_
#include <GL/freeglut.h>
#include "Picking.h"
#include "RotationLimits.h"
#include "MaterialColor.h"

class Shape
{
private:
	int pickIndex;
	int rotX;
	int rotY;
	int rotZ;
protected:
	RotationLimits* rot;
public:
	Shape(void);
	~Shape(void);

	int GetPickIndex(void);
	void CreatePickable(void);
	bool IsSelected(void);

	void GetRotations(void);

	virtual void Draw(void) = 0;
	virtual void RotateObject(int, int);

	MaterialColor* mat;
};
#endif

