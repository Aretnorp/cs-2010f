/*
 * =====================================================================================
 *
 *       Filename:  Arm.cpp
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
#include "Arm.h"

/*-----------------------------------------------------------------------------
 *  Arm
 *  Creates an Arm
 *-----------------------------------------------------------------------------*/
Arm::Arm(bool isLeft)
{
        RotationLimits* rot;

        // Create the Upper Arm
        rot = new RotationLimits();
        if(isLeft)
        {
        rot->minX = -90;
        rot->minY = -90;
            //rot->maxZ = 180;
        }
        else
        {
                rot->maxX = 90;
                rot->maxY = 90;
                //rot->maxZ = 180;
        }
        this->upperArm = new Square(10, rot);
        this->upperArm->mat->SetAllColors(1.0, 0.0, 0.0, 1.0);

        // Create the Lower Arm
        rot = new RotationLimits();
        if(isLeft)
        {
            rot->maxX = 90;
            rot->minY = -90;
        }
        else
        {
                rot->minX = -90;
                rot->maxY = 90;
        }
        this->lowerArm = new Square(10, rot);
        this->lowerArm->mat->SetAllColors(0.0, 0.0, 1.0, 1.0);

        // Add the Shapes to the container
        this->AddShape(this->upperArm);
        this->AddShape(this->lowerArm);
}

/*-----------------------------------------------------------------------------
 *  ~Arm
 *  Destroys the Arm object
 *-----------------------------------------------------------------------------*/
Arm::~Arm(void)
{
        // Clean out memory
        delete this->upperArm;
        delete this->lowerArm;
}

/*-----------------------------------------------------------------------------
 *  Draw
 *  Draws out an Arm with its joints
 *-----------------------------------------------------------------------------*/
void Arm::Draw(void)
{
        // Draw the first arm
        this->upperArm->Draw();

        glPushMatrix( );
        // Move to the end of the joint
                this->upperArm->GetJoint( );

        // Illustrate the joint
        glutSolidSphere(5, 10, 10);

                // Create the Lower Arm
                this->lowerArm->Draw();

                glPushMatrix( );
                        // Move to the end of the joint
                this->lowerArm->GetJoint( );

                        // Create the hand
                        glTranslatef(0.0, 0.0, 2.5);
                        glutSolidSphere(4.0, 10, 10);
                glPopMatrix( );
    glPopMatrix( );
}

/*-----------------------------------------------------------------------------
 *  RotateObject
 *  Propogates its rotates on to its container objects
 *-----------------------------------------------------------------------------*/
void Arm::RotateObject(int x, int y)
{
        // Call rotates on container
        this->RotateObjects(x, y);
}
