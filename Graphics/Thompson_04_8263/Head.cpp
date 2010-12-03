/*
 * =====================================================================================
 *
 *       Filename:  Head.cpp
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
#include "Head.h"
#include "texture.h"
#include "texture.c"

GLUquadricObj *sphere;
GLuint texture[1]; /* Textures */

/*-----------------------------------------------------------------------------
*  Head
*  Creates a Head object
*-----------------------------------------------------------------------------*/
Head::Head(int size, RotationLimits* rot)
{
	this->size = size;
	this->head = new Square(this->size, rot);

	// Load the texture
	glGenTextures(1, texture);
	LoadTexture("earth.rgb", 0);

	// Enable textures
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	// Load the textures
	this->index = glGenLists(1);
	sphere = gluNewQuadric();
	gluQuadricTexture(sphere, GL_TRUE);

	// Enable texturing
	glEnable(GL_TEXTURE_2D);

	// Create the eye list
	glNewList(this->index, GL_COMPILE);
		// Scale for the Sphere
		glScalef(this->size / 2, this->size / 4, this->size);

		// Create the Sphere
		gluSphere(sphere, 1.0, 10, 10);
	glEndList();

	// Disable texturing
	glDisable(GL_TEXTURE_2D);
}

/*-----------------------------------------------------------------------------
*  ~Head
*  Deletes the Head object
*-----------------------------------------------------------------------------*/
Head::~Head(void)
{
	delete this->head;
}

/*-----------------------------------------------------------------------------
*  Draw
*  Draws the Head and a Single eye-ball
*-----------------------------------------------------------------------------*/
void Head::Draw(void)
{
	glPushMatrix();
    	// First, create the square
    	this->head->Draw();

    	// Next, position ourselves for the eye
    	glTranslatef(0.0, -(this->size / 2), this->size);

		// Enable texturing
		glEnable(GL_TEXTURE_2D);

		// Create the Sphere
		glCallList(this->index);

		// Disable texturing
		glDisable(GL_TEXTURE_2D);
	glPopMatrix( );
}


/*-----------------------------------------------------------------------------
*  RotateObject
*  Rotates the Head object
*-----------------------------------------------------------------------------*/
void Head::RotateObject(int x, int y)
{
	this->head->RotateObject(x, y);
}


/*-----------------------------------------------------------------------------
*  LoadTexture
*  Provided function to load textures from rgb file
*-----------------------------------------------------------------------------*/
void Head::LoadTexture(char *fn, int t_num)
{
	int texwid, texht;
	int texcomps;
	unsigned *teximage;
 
	teximage = read_texture(fn, &texwid, &texht, &texcomps);
	if (!teximage)
	{
		printf("Sorry, can't read texture file...");
		exit(0);
	}
	glBindTexture(GL_TEXTURE_2D, texture[t_num]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texwid, texht, 0, GL_RGBA, GL_UNSIGNED_BYTE, teximage);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texwid, texht, GL_RGBA, GL_UNSIGNED_BYTE, teximage);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

	free(teximage);
} 
