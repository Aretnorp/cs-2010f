/*
 * =====================================================================================
 *
 *       Filename:  main.h
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
#ifndef __MAIN_H_
#define __MAIN_H_
/*-----------------------------------------------------------------------------
*  Include the headers
*-----------------------------------------------------------------------------*/
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <GL/freeglut.h>

#include "Person.h"
#include "Picking.h"
#include "Menu.h"

#define TRUE 1
#define FALSE 0

#define DEFAULT_FONT GLUT_BITMAP_8_BY_13
#define BUF_SIZ 256

#define N 1
#define MATRIX_SIZE 16


/*-----------------------------------------------------------------------------
*  Function Definitions
*-----------------------------------------------------------------------------*/
void Draw( void );
void Keyboard( unsigned char, int, int );
void SpecialKeyboard( int, int, int );
void CreateText( float x, float y, void* font, char* buf);
void ClearMemory( void );
void Reshape( int width, int height );
void ProcessHits( GLint hits, GLuint buffer[] );
void Mouse(int button, int state, int x, int y);
void MouseMove( int x, int y );
void Reset( void );
void EnableLighting( void );

#endif
