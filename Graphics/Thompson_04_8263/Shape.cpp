/*
 * =====================================================================================
 *
 *       Filename:  Shape.cpp
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
#include "Shape.h"


/*-----------------------------------------------------------------------------
*  Shape
*  Creates a new Shape with no set rotations and default RotationLimits and
*  MaterialColor
*-----------------------------------------------------------------------------*/
Shape::Shape(void)
{
	// Assign the Pick Index
	this->pickIndex = Picking::GetNextIndex();

	// Initialize rotations
	this->rotX = this->rotY = this->rotZ = 0;

	// Initialize rotation limits
	this->rot = new RotationLimits();

	// Initialize colors
	this->mat = new MaterialColor();
}

/*-----------------------------------------------------------------------------
*  ~Shape
*  Destroy a Shape object
*-----------------------------------------------------------------------------*/
Shape::~Shape(void)
{
	// Clear used memory
	delete this->rot;
	delete this->mat;
}

/*-----------------------------------------------------------------------------
*  Draw
*  Initialize each parameter (picking, line/fill, rotations, and color)
*  for drawing
*-----------------------------------------------------------------------------*/
void Shape::Draw(void)
{
	// Set the name of the object
	this->CreatePickable();

	// Check if its selected
	if(this->IsSelected())
		glPolygonMode(GL_FRONT, GL_LINE);
	else
		glPolygonMode(GL_FRONT, GL_FILL);

	// Do the rotations
	this->GetRotations();

	// Get the colors
	this->mat->GetMaterialColors();
}

/*-----------------------------------------------------------------------------
*  GetPickIndex
*  Return the currently selected PickIndex
*-----------------------------------------------------------------------------*/
int Shape::GetPickIndex(void)
{
	return this->pickIndex;
}

/*-----------------------------------------------------------------------------
*  CreatePickable
*  Loads the name index for this object
*-----------------------------------------------------------------------------*/
void Shape::CreatePickable(void)
{
	// Use the SetName function
	glLoadName(this->pickIndex);
}

/*-----------------------------------------------------------------------------
*  IsSelected
*  Indicates whether or not an index is included in the selected set
*-----------------------------------------------------------------------------*/
bool Shape::IsSelected(void)
{
	// Determine if the object is selected
	return Picking::IsSelectedIndex(this->pickIndex);
}

/*-----------------------------------------------------------------------------
*  RotateObject
*  Indicates whether or not an object has been selected and if it can be
*  rotated. Rotates based on x y
*-----------------------------------------------------------------------------*/
void Shape::RotateObject(int x, int y)
{
	if(this->IsSelected())
	{
		int z = y;

    	// Rotate around the x dimension
    	if(x < this->rot->minX)
    		x = this->rot->minX;
    	else if(x > this->rot->maxX)
    		x = this->rot->maxX;
    	this->rotX = x;
    
    	// Rotate around the y dimension
    	if(y < this->rot->minY)
    		y = this->rot->minY;
    	else if(y > this->rot->maxY)
    		y = this->rot->maxY;
    	this->rotY = y;
    
    	// Rotate around the z dimension
    	if(z < this->rot->minZ)
			z = this->rot->minZ;
		else if(z > this->rot->maxZ)
			z = this->rot->maxZ;
		this->rotZ = z;
	}
}

/*-----------------------------------------------------------------------------
*  GetRotations
*  Includes the Rotations done in OpenGL for the rotations
*-----------------------------------------------------------------------------*/
void Shape::GetRotations(void)
{
	// Rotate around a given axis
	glRotatef(this->rotX, 1.0, 0.0, 0.0);
	glRotatef(this->rotY, 0.0, 1.0, 0.0);
	glRotatef(this->rotZ, 0.0, 0.0, 1.0);
}
