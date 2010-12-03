#include "ShapeContainer.h"


/*-----------------------------------------------------------------------------
*  ShapeContainer
*  Creates a new ShapeContainer
*-----------------------------------------------------------------------------*/
ShapeContainer::ShapeContainer(void)
{
}

/*-----------------------------------------------------------------------------
*  ~ShapeContainer
*  Destroys a ShapeContainer
*-----------------------------------------------------------------------------*/
ShapeContainer::~ShapeContainer(void)
{
}

/*-----------------------------------------------------------------------------
*  AddShape
*  Adds a new Shape to the Shape Container
*-----------------------------------------------------------------------------*/
void ShapeContainer::AddShape(Shape* s)
{
	this->components.push_back(s);
}

/*-----------------------------------------------------------------------------
*  RemoveShape
*  Removes a Shape from the Shape Container
*-----------------------------------------------------------------------------*/
void ShapeContainer::RemoveShape(Shape* s)
{
	this->components.remove(s);
}

/*-----------------------------------------------------------------------------
*  RotateObjects
*  Rotates each Object within a Shape Container
*-----------------------------------------------------------------------------*/
void ShapeContainer::RotateObjects(int x, int y)
{
	// For each stored object, rotate to given x + y
	for(std::list<Shape*>::iterator it = this->components.begin();
		it != this->components.end(); ++it)
		(*it)->RotateObject(x, y);
}

