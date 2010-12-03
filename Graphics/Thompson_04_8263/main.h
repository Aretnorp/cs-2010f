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
