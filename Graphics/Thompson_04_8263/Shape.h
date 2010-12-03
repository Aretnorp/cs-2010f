/*
 * =====================================================================================
 *
 *       Filename:  Shape.h
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

