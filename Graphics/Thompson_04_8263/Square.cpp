/*
 * =====================================================================================
 *
 *       Filename:  Square.cpp
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
#include "Square.h"

/*-----------------------------------------------------------------------------
*  Square
*  Creates a new Square for a given size and set of rotations
*-----------------------------------------------------------------------------*/
Square::Square(int size, RotationLimits* rot)
{
	this->size = size;
	this->rot = rot;

	// Create the List for the Shape
	this->index = glGenLists(1);
	glNewList(this->index, GL_COMPILE);
    	// Scale the plane to give us a more rectangular prism
    	glScalef(1.0, 1.0, 2.0);
    
    	// I know that the Cube is made perfectly around 
		// origin equally in each direction
    	glTranslatef(0.0, 0.0, this->size / 2);
    
    	// Create the Primitive for the Square
    	glutSolidCube(this->size);
	glEndList( );
}

/*-----------------------------------------------------------------------------
*  ~Square
*  Destroys a Square
*-----------------------------------------------------------------------------*/
Square::~Square(void)
{
}

/*-----------------------------------------------------------------------------
*  Draw
*  Draws a Square on to the screen
*-----------------------------------------------------------------------------*/
void Square::Draw(void)
{
    // Do the drawing
	Shape::Draw();

	glPushMatrix( );
		// Use the list
		glCallList(this->index);
	glPopMatrix( );
}

/*-----------------------------------------------------------------------------
*  GetJoint
*  Returns the opposite end of a given square
*-----------------------------------------------------------------------------*/
void Square::GetJoint(void)
{
	// Translate to the next point for a Joint
	glTranslatef(0.0, 0.0, this->size * 2 + 2.5);
}

