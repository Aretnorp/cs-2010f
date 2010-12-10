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
#include "normal.c"

GLUquadricObj *sphere;
GLuint texture[1]; /* Textures */

/*-----------------------------------------------------------------------------
*  Head
*  Creates a Head object
*-----------------------------------------------------------------------------*/
Head::Head(int size, RotationLimits* rot)
{
        this->size = size;
        this->rot = rot;

        // Load the texture
        glGenTextures(1, texture);
        char file[] = "eye.rgb";
        LoadTexture(file, 0);

        // Enable textures
        glBindTexture(GL_TEXTURE_2D, texture[0]);

        // Load the textures
        this->index = glGenLists(2);
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

        // Create the Pyramid list
        const GLfloat V0[] = { this->size, this->size, 0.0 };
        const GLfloat V1[] = { -this->size, this->size, 0.0 };
        const GLfloat V2[] = { -this->size, -this->size, 0.0 };
        const GLfloat V3[] = { this->size, -this->size, 0.0 };
        const GLfloat T0[] = { 0.0, 0.0, this->size };
        glNewList(this->index + 1, GL_COMPILE);
                // Create the Pyramid
                glBegin(GL_QUADS);
                        glNormal3fv(UnitNormal(V3[0], V3[1], V3[2],
                                               V2[0], V2[1], V2[2],
                                               V1[0], V1[1], V1[2]));
                        glNormal3fv(UnitNormal(V3[0], V3[1], V3[2],
                                               V1[0], V1[1], V1[2],
                                               V0[0], V0[1], V0[2]));
                        glVertex3fv(V3);
                        glVertex3fv(V2);
                        glVertex3fv(V1);
                        glVertex3fv(V0);
                glEnd( );
                glBegin(GL_TRIANGLE_FAN);
                        glNormal3fv(UnitNormal(T0[0], T0[1], T0[2],
                                               V0[0], V0[1], V0[2],
                                               V1[0], V1[1], V1[2]));
                        glVertex3fv(T0);
                        glVertex3fv(V0);
                        glVertex3fv(V1);

                        glNormal3fv(UnitNormal(T0[0], T0[1], T0[2],
                                               V1[0], V1[1], V1[2],
                                               V2[0], V2[1], V2[2]));
                        glVertex3fv(V2);

                        glNormal3fv(UnitNormal(T0[0], T0[1], T0[2],
                                               V2[0], V2[1], V2[2],
                                               V3[0], V3[1], V3[2]));
                        glVertex3fv(V3);

                        glNormal3fv(UnitNormal(T0[0], T0[1], T0[2],
                                               V3[0], V3[1], V3[2],
                                               V0[0], V0[1], V0[2]));\
                        glVertex3fv(V0);
                glEnd( );
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
}

/*-----------------------------------------------------------------------------
*  Draw
*  Draws the Head and a Single eye-ball
*-----------------------------------------------------------------------------*/
void Head::Draw(void)
{
        glPushMatrix();
                // First, create the square
                Shape::Draw();
                glCallList(this->index + 1);

                // Next, position ourselves for the eye
                glTranslatef(0.0, 0.0, this->size);

                glPushMatrix( );
                        // Enable texturing
                        glEnable(GL_TEXTURE_2D);

                        // Create the Sphere
                        glCallList(this->index);

                        // Disable texturing
                        glDisable(GL_TEXTURE_2D);
                glPopMatrix( );
        glPopMatrix( );
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
