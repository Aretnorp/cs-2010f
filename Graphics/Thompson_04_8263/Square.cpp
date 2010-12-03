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

