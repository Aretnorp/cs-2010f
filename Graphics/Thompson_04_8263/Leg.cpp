/*
 * =====================================================================================
 *
 *       Filename:  Leg.cpp
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
#include "Leg.h"

/*-----------------------------------------------------------------------------
 *  Leg
 *  Creates a Leg
 *-----------------------------------------------------------------------------*/
Leg::Leg(void)
{
	RotationLimits* rot;

	// Create the Upper Leg
	rot = new RotationLimits();
	rot->minX = -45;
	rot->maxX = 45;
	this->upperLeg = new Square(10, rot);
	this->upperLeg->mat->SetAllColors(0.5, 0.5, 0.0, 1.0);

	// Create the Lower Leg
	rot = new RotationLimits();
	rot->maxX = 90;
	this->lowerLeg = new Square(10, rot);
	this->lowerLeg->mat->SetAllColors(0.5, 0.0, 0.5, 1.0);

	// Create the Foot
	rot = new RotationLimits();
	rot->minX = -45;
	this->foot = new Square(5, rot);
	this->foot->mat->SetAllColors(0.0, 0.5, 0.5, 1.0);

	// Add the Shapes to the container
	this->AddShape(this->upperLeg);
	this->AddShape(this->lowerLeg);
	this->AddShape(this->foot);
}

/*-----------------------------------------------------------------------------
 *  ~Leg
 *  Destroys a Leg
 *-----------------------------------------------------------------------------*/
Leg::~Leg(void)
{
	// Clean out memory
	delete this->upperLeg;
	delete this->lowerLeg;
}

/*-----------------------------------------------------------------------------
 *  Draw
 *	Draws a Leg and its Joints
 *-----------------------------------------------------------------------------*/
void Leg::Draw(void)
{
	// Draw the first arm
	this->upperLeg->Draw();

	glPushMatrix( );
    	// Move to the end of the joint
		this->upperLeg->GetJoint();

    	// Illustrate the joint
    	glutSolidSphere(5, 10, 10);

		// Create the Lower Leg
		this->lowerLeg->Draw();

		glPushMatrix( );
			// Move to the end of the joint
			this->lowerLeg->GetJoint();

			// Illustrate the Joint
			glutSolidSphere(2.5, 10, 10);

			// Create the Foot
			this->foot->Draw();
		glPopMatrix( );
    glPopMatrix( );
}

/*-----------------------------------------------------------------------------
 *  RotateObject
 *  Propagates rotate call down to children
 *-----------------------------------------------------------------------------*/
void Leg::RotateObject(int x, int y)
{
	// Call rotates on container
	this->RotateObjects(x, y);
}


