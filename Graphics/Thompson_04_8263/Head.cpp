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
