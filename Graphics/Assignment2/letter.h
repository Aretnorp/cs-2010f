/*
 * =====================================================================================
 *
 *       Filename:  letter.h
 *
 *    Description:  Defines a letter in 3D using GL Primitives
 *
 *        Version:  1.0
 *
 *         Author:  Cody Thompson
 *
 *     Difficulty:  The most difficult aspect was creating the proper perspective. Due
 *                  to the differences between the Projection Matrix and ModelView
 *                  Matrix, I had to learn how to do the proper implementation.
 *     Objectives:  Create an object in 3D using GL Primitives. Render the object in
 *                  3D. Use a proper perspective that shows the shape as a 3D object.
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
