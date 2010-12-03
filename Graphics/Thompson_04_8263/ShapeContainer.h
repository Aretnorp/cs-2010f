#ifndef __SHAPE_CONTAINER_H_
#define __SHAPE_CONTAINER_H_
#include <list>
#include "Shape.h"

class ShapeContainer
{
private:
	std::list<Shape*> components;
protected:
	void AddShape(Shape*);
	void RemoveShape(Shape*);
public:
	ShapeContainer(void);
	~ShapeContainer(void);
	void RotateObjects(int, int);
};
#endif

