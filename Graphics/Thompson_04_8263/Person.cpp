/*
 * =====================================================================================
 *
 *       Filename:  Person.cpp
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
#include "Person.h"

/*-----------------------------------------------------------------------------
*  Person
*  Creates a new instance of a Person with the proper properties
*-----------------------------------------------------------------------------*/
Person::Person(void)
{
	RotationLimits* rot;

	// Create the necessary shapes
    rot = new RotationLimits();
	rot->minY = -30;
	rot->maxY = 30;
	this->torso = new Torso(30, 40);

	// Create the Arms and Legs
	this->rightArm = new Arm(false);
	this->leftArm = new Arm(true);
	this->rightLeg = new Leg();
	this->leftLeg = new Leg();

	// Create the Head
	rot = new RotationLimits();
	rot->minZ = -45;
	rot->maxZ = 45;
	this->head = new Head(20, rot);

	// Add the Shapes to the container
	this->AddShape(this->torso);
	this->AddShape(this->rightArm);
	this->AddShape(this->leftArm);
	this->AddShape(this->rightLeg);
	this->AddShape(this->leftLeg);
	this->AddShape(this->head);
}

/*-----------------------------------------------------------------------------
*  ~Person
*  Clears the memory consumed by the person
*-----------------------------------------------------------------------------*/
Person::~Person(void)
{
	// Delete the memory
	delete this->torso;
	delete this->rightArm;
	delete this->leftArm;
	delete this->rightLeg;
	delete this->leftLeg;
	delete this->head;
}

/*-----------------------------------------------------------------------------
*  Draw
*  Draws each person consequentially and uses the joints contained in the
*  Torso
*-----------------------------------------------------------------------------*/
void Person::Draw(void)
{
	// Draw the Torso
	this->torso->Draw();

	glPushMatrix( );
    	// Position for the head
    	this->torso->MoveToHead();

		// Draw the Head
		this->head->Draw();
    glPopMatrix( );

	// Position for each arms
	glPushMatrix( );
    	this->torso->MoveToLeftArm();

		// Draw the Left Arm
		this->leftArm->Draw();
    glPopMatrix( );
	glPushMatrix( );
    	this->torso->MoveToRightArm();

		// Draw the Right Arm
		this->rightArm->Draw();
	glPopMatrix( );

	// Position for the Legs
	glPushMatrix( );
    	this->torso->MoveToLeftLeg();

		// Draw the Left Leg
    	this->leftLeg->Draw();
	glPopMatrix( );
	glPushMatrix( );
    	this->torso->MoveToRightLeg();

		// Draw the Right Leg
    	this->rightLeg->Draw();
	glPopMatrix( );
}
