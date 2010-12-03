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


