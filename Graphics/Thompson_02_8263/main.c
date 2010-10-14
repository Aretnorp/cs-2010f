/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Draws a Letter in 3D
 *
 *        Version:  1.0
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
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>

#include "letter.h"

#define TRUE 1
#define FALSE 0

/*-----------------------------------------------------------------------------
 *  Function Definitions
 *-----------------------------------------------------------------------------*/
void Draw( void );
void Reshape( int, int );
void Keyboard( unsigned char , int , int );
void ClearMemory( void );

/*-----------------------------------------------------------------------------
 *  Variable Definitions
 *-----------------------------------------------------------------------------*/
GLfloat rotX = 0;
GLfloat rotY = 0;
int radius = 250;

GLenum mode = GL_FILL;
char letter = 't';

/*-----------------------------------------------------------------------------
 *  Main Function
 *  Initiates the graphics buffer, creates the window and calls InitShapes
 *-----------------------------------------------------------------------------*/
int main( int argc, char *argv[] )
{
    /* Initialize the drawing environment */
    glutInit( &argc, argv );

    /* Initialize the display mode */
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE );

    /* Create an application window of a certain size */
    glutInitWindowSize( 600, 600 );

    /* Create an application window on the screen */
    glutCreateWindow( "Assignment #2: 3D Letter" );

    /* Register the function that does drawing */
    glutDisplayFunc( Draw );

    /* Create the Keyboard callback */
    glutKeyboardFunc( Keyboard );

    /* Create the Reshape callback */
    glutReshapeFunc( Reshape );

    /* Enable GL Properties */
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    /* Register Exit Handler */
    atexit(ClearMemory);

    /* Initialize the Shape Lists */
    InitShapes();

    /* Turn over control to OpenGL */
    glutMainLoop();

    return( 0 );  /* NOTE: this is here only for ANSI requirements */
}

/*-----------------------------------------------------------------------------
 *  Keyboard
 *  Handles the keyboard input for each of the various buttons
 *-----------------------------------------------------------------------------*/
void Keyboard( unsigned char key, int x, int y )
{
    /* Determine which key is pressed */
    switch(key)
    {
        /* Right */
        case 'd':
            rotY++; break;
        case 'D':
            rotY += 10; break;
        /* Left */
        case 'a':
            rotY--; break;
        case 'A':
            rotY -= 10; break;
        /* Up */
        case 'w':
            rotX++; break;
        case 'W':
            rotX += 10; break;
        /* Down */
        case 's':
            rotX--; break;
        case 'S':
            rotX -= 10; break;
        /* Wireframe Modes */
        case 'F':
            mode = GL_FILL; break;
        case 'L':
            mode = GL_LINE; break;
        /* Letter Types */
        case 'Q':
            if(letter == 't')
                letter = 'T';
            else
                letter = 't';
            break;
        default: return; /* Exit if another key was pressed */
    }

    /* Reshape the Display */
    Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

    /* Redraw the Display */
    glutPostRedisplay();
}

/*-----------------------------------------------------------------------------
 *  Reshape
 *  Handles the perspective resize etc when the screen changes in size from
 *  dragging and dropping.
 *-----------------------------------------------------------------------------*/
void Reshape( int width, int height )
{
    /* Change to Projection Matrix */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    /* Configure Viewport */
    glViewport(0, 0, width, height);

    /* Configure Perspective to proper aspect ratio */
    gluPerspective( 45.0, width / height, 1.0, 500 );

    /* Look at Origin from specified angle */
    gluLookAt(0.0, 0.0, radius,
              0.0, 0.0, 0.0, /* Look at Center */
              0.0, 1.0, 0.0); /* Look up */

    /* Change to ModelView Matrix */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

}

/*-----------------------------------------------------------------------------
 *  ClearMemory
 *  Clears the dynamically allocated memory at close
 *-----------------------------------------------------------------------------*/
void ClearMemory( void )
{
    /* Clear dynamically allocated memory */
    glDeleteLists( tLists, NUM_LISTS );
}

/*-----------------------------------------------------------------------------
 *  Draw
 *  The Draw function is the main loop for the Graphics process. Draws the
 *  letter by using the CallList and handles rotating the scene
 *-----------------------------------------------------------------------------*/
void Draw( void )
{
    /* Clear the screen ... */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* Do the Rotation */
    glLoadIdentity();
    glRotatef( rotX, 1.0, 0.0, 0.0 );
    glRotatef( rotY, 0.0, 1.0, 0.0 );

    /* Set the Polygon Mode */
    glPolygonMode(GL_FRONT, mode);

    /* Call for the List */
    glCallList(letter);

    /* Flush the buffer */
    glutSwapBuffers( ); 

    return;
}
