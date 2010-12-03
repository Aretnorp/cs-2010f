/*
 * =====================================================================================
 *
 *       Filename:  Torso.h
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

