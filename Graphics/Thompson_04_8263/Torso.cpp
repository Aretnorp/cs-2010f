/*
 * =====================================================================================
 *
 *       Filename:  Torso.cpp
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
#include "Torso.h"

/*-----------------------------------------------------------------------------
*  Torso
*  Creates a Torso object
*-----------------------------------------------------------------------------*/
Torso::Torso(int width, int height, RotationLimits* rot)
{
	this->width = width;
	this->height = height * 2;
	this->mat->SetAllColors(0.0, 1.0, 0.0, 1.0);

	// Create the List for the Shape
	this->index = glGenLists(1);
	glNewList(this->index, GL_COMPILE);
    	glPushMatrix( );
        	//Scale to the size of the Torso
        	glScalef(this->width, this->height, 15.0);
        
        	// Create the Torso
        	glutSolidCube(1.0);
    	glPopMatrix( );
    
    	// Create each of the Joints
    	glPushMatrix( );
        	this->MoveToHead( );
        	glutSolidSphere(7.5, 10, 10);
        glPopMatrix( );
    
    	glPushMatrix( );
        	this->MoveToLeftArm( );
        	glutSolidSphere(5.0, 10, 10);
    	glPopMatrix( );
    
    	glPushMatrix( );
        	this->MoveToRightArm( );
        	glutSolidSphere(5.0, 10, 10);
    	glPopMatrix( );
    
    	glPushMatrix( );
        	this->MoveToLeftLeg( );
        	glutSolidSphere(5.0, 10, 10);
    	glPopMatrix( );
    
    	glPushMatrix( );
        	this->MoveToRightLeg( );
        	glutSolidSphere(5.0, 10, 10);
    	glPopMatrix( );
	glEndList( );
}

/*-----------------------------------------------------------------------------
*  ~Torso
*  Destroys a Torso object
*-----------------------------------------------------------------------------*/
Torso::~Torso(void)
{
}

/*-----------------------------------------------------------------------------
*  Draw
*  Draws a Torso object with its joints on to the screen
*-----------------------------------------------------------------------------*/
void Torso::Draw(void)
{
	// Call the Parent Draw
	Shape::Draw();

	// Call the List
	glCallList(this->index);
}

/*-----------------------------------------------------------------------------
*  MoveToRightArm
*  Moves to the Right Arm Joint
*-----------------------------------------------------------------------------*/
void Torso::MoveToRightArm(void)
{
	// Transform to the location of the Right Arm
	glTranslatef(-(this->width / 2) - 5, this->height / 2, 0);

	// Rotate the axis to show the arm
	glRotatef(-90.0, 0.0, 1.0, 0.0);
}

/*-----------------------------------------------------------------------------
*  MoveToLeftArm
*  Moves to the Left Arm Joint
*-----------------------------------------------------------------------------*/
void Torso::MoveToLeftArm(void)
{
	// Transform to the location of the Left Arm
	glTranslatef(this->width / 2 + 5, this->height / 2, 0);

	// Rotate the axis to show the arm
	glRotatef(90.0, 0.0, 1.0, 0.0);
}

/*-----------------------------------------------------------------------------
*  MoveToRightLeg
*  Moves to the Right Leg Joint
*-----------------------------------------------------------------------------*/
void Torso::MoveToRightLeg(void)
{
	// Transform to the location of the Right Leg
	glTranslatef(-(this->width / 2 - (this->width * 0.25)), 
				 -(this->height / 2) - 5, 0);

	// Rotate the axis to show the leg
	glRotatef(90.0, 1.0, 0.0, 0.0);
}

/*-----------------------------------------------------------------------------
*  MoveToLeftLeg
*  Moves to the Left Leg Joint
*-----------------------------------------------------------------------------*/
void Torso::MoveToLeftLeg(void)
{
	// Transform to the location of the Left Leg
	glTranslatef(this->width / 2 - (this->width * 0.25), 
				 -(this->height / 2) - 5, 0);

	// Rotate the axis to show the leg
	glRotatef(90.0, 1.0, 0.0, 0.0);
}

/*-----------------------------------------------------------------------------
*  MoveToHead
*  Moves to the Head Joint
*-----------------------------------------------------------------------------*/
void Torso::MoveToHead(void)
{
	// Transform to the location of the Head
	glTranslatef(0.0, (this->height / 2) + 7.5, 0.0);

	// Rotate the axis to show the head
	glRotatef(-90.0, 1.0, 0.0, 0.0);
}