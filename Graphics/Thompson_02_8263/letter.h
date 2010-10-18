/*
 * =====================================================================================
 *
 *       Filename:  letter.h
 *
 *    Description:  Draws a Letter in 3D
 *
 *        Version:  1.0
 *
 *           Date: October 15th, 2010
 *
 *         Author:  Cody Thompson
 *
 *     Difficulty:  The most difficult aspect was creating the proper perspective. Due
 *                  to the differences between the Projection Matrix and ModelView
 *                  Matrix, I had to learn how to do the proper implementation.
 *                  The level of difficulty was: 2
 *     Objectives:  Create an object in 3D using GL Primitives. Render the object in
 *                  3D. Use a proper perspective that shows the shape as a 3D object.
 *       Comments:  Two things that need to be noted:
 *                  A) I've used multi-sampling to round the edges of the shape
 *                     and this method is much more obvious/simple than using the
 *                     FSAA of prior times (GLUT_MULTISAMPLE on Window, and
 *                     glEnable(GL_MULTISAMPLE))
 *                  B) The reason I use the variable 'letter' is because I've created
 *                     two displays lists for two different variants on the T. My
 *                     first T used a simple set of 16 vertices and created primitives
 *                     between them. This is more of a basic T and didn't take into
 *                     account any depth on the shape in the letter that was provided.
 *                     The second T shown is the one that has a recessed inner side,
 *                     making the top larger and sticking out. The primary difference
 *                     is that a few extra calls to various primitives were used to
 *                     model the underside of it. In all cases, I used sets of
 *                     primitives and did not combine cubes.
 * =====================================================================================
 */

/*-----------------------------------------------------------------------------
 *  Include the headers
 *-----------------------------------------------------------------------------*/
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define NUM_LISTS 2

/*-----------------------------------------------------------------------------
 *  Variable Definitions
 *-----------------------------------------------------------------------------*/
GLuint tLists;

/*-----------------------------------------------------------------------------
 *  Function Definitions
 *-----------------------------------------------------------------------------*/
void InitShapes( void );
