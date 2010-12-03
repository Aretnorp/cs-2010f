/*
 * =====================================================================================
 *
 *       Filename:  ShapeContainer.cpp
 *
 *    Description:  Creates a Puppet model that can be modified via the joints
 *
 *        Version:  1.0
 *        Created:  November 30th, 2010
 *
 *         Author:  Cody Thompson
 *
 *     Difficulty:  The most difficult aspect was the creation of the actual object
 *                  itself which in retrospect I should have not done in such a 
 *                  complex and otherwise complicated manner. Aside from that, minor
 *                  issues with my artistic prowess in terms of developing an eye
 *                  appealing model.
 *     Objectives:  To learn how to create a complex OpenGL application using the
 *                  various things we have learned in this course.
 *           1. To understand hierarchical models
 *           2. To manipulate the matrix stack
 *           3. To work with the zbuffer and back facing polygons
 *           4. To use hidden surface removal
 *           5. To use a display list
 *           6. To use the perspective transformations
 *           7. To create Menus using the glut library
 *           8. To pick and select different objects
 *           9. To manipulate objects using the mouse
 *           10.To add lighting to complex objects
 *           11.To apply material to objects instead of colors
 *           12.To add textures to complex objects
 * =====================================================================================
 */
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

