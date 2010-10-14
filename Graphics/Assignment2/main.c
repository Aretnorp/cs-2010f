/*
 * =====================================================================================
 *
 *       Filename:  Thompson_02_8263.c
 *
 *    Description:  Provides an interface to create Star Polygons
 *
 *        Version:  1.0
 *        Created:  09/22/2010 10:38:14 AM
 *
 *         Author:  Cody Thompson
 *
 *     Difficulty:  The most difficult aspect was the calculation for Star Polygons.
 *                  It took an approximately an hour to come up with the calculation.
 *                  Overall, the project was very easy.
 *     Objectives:  To learn how to create a simple OpenGL application and understand
 *                  how viewports and line drawing works.
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

#define TRUE 1
#define FALSE 0

#define NUM_LISTS 2

/*-----------------------------------------------------------------------------
 *  Function Definitions
 *-----------------------------------------------------------------------------*/
void Draw( void );
void Reshape( int, int );
void Keyboard( unsigned char , int , int );
void ClearMemory( void );
void InitShapes( void );

/*-----------------------------------------------------------------------------
 *  Variable Definitions
 *-----------------------------------------------------------------------------*/
GLfloat rotX = 0;
GLfloat rotY = 0;
int radius = 250;

GLuint tLists;
GLenum mode = GL_FILL;
char letter = 't';

/*-----------------------------------------------------------------------------
 *  Main Function
 *  Initiates the graphics buffer, creates the window and CalculatePoints
 *-----------------------------------------------------------------------------*/
int main( int argc, char *argv[] )
{
    /* Initialize the drawing environment */
    glutInit( &argc, argv );

    /* Initialize the display mode */
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_DEPTH );

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
 *  Keyboard
 *  Handles the keyboard input for each of the various buttons
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
 *  Keyboard
 *  Handles the keyboard input for each of the various buttons
 *-----------------------------------------------------------------------------*/
void InitShapes ( )
{
    /* Create a List */
    tLists = glGenLists(NUM_LISTS);

    /* Define the List */
    glNewList( 't', GL_COMPILE );

        /* Draw the Front Face */
        glColor3f(1.0, 0.0, 0.0);
        glBegin( GL_POLYGON );
            glVertex3f( -10.0, 30.0, 12.5 );
            glVertex3f( -10.0,-50.0, 12.5 );
            glVertex3f(  10.0,-50.0, 12.5 );
            glVertex3f(  10.0, 30.0, 12.5 );
            glVertex3f(  37.5, 30.0, 12.5 );
            glVertex3f(  37.5, 50.0, 12.5 );
            glVertex3f( -37.5, 50.0, 12.5 );
            glVertex3f( -37.5, 50.0, 12.5 );
            glVertex3f( -37.5, 30.0, 12.5 );
        glEnd( );

        /* Draw the Back Face */
        glColor3f(0.0, 1.0, 0.0);
        glBegin( GL_POLYGON );
            glVertex3f(  10.0, 30.0,-12.5 );
            glVertex3f(  10.0,-50.0,-12.5 );
            glVertex3f( -10.0,-50.0,-12.5 );
            glVertex3f( -10.0, 30.0,-12.5 );
            glVertex3f( -37.5, 30.0,-12.5 );
            glVertex3f( -37.5, 50.0,-12.5 );
            glVertex3f(  37.5, 50.0,-12.5 );
            glVertex3f(  37.5, 30.0,-12.5 );
        glEnd( );

        /* Draw the Inner Sides */
        glColor3f(0.0, 0.0, 1.0);
        glBegin( GL_QUAD_STRIP );
            glVertex3f(  37.5, 50.0,-12.5 );
            glVertex3f(  37.5, 50.0, 12.5 );
            glVertex3f(  37.5, 30.0,-12.5 );
            glVertex3f(  37.5, 30.0, 12.5 );
            glVertex3f(  10.0, 30.0,-12.5 );
            glVertex3f(  10.0, 30.0, 12.5 );
            glVertex3f(  10.0,-50.0,-12.5 );
            glVertex3f(  10.0,-50.0, 12.5 );
            glVertex3f( -10.0,-50.0,-12.5 );
            glVertex3f( -10.0,-50.0, 12.5 );
            glVertex3f( -10.0, 30.0,-12.5 );
            glVertex3f( -10.0, 30.0, 12.5 );
            glVertex3f( -37.5, 30.0,-12.5 );
            glVertex3f( -37.5, 30.0, 12.5 );
            glVertex3f( -37.5, 50.0,-12.5 );
            glVertex3f( -37.5, 50.0, 12.5 );
            glVertex3f(  37.5, 50.0,-12.5 );
            glVertex3f(  37.5, 50.0, 12.5 );
        glEnd( );

    /* End the List */
    glEndList( );

    /* Define the List */
    glNewList( 'T', GL_COMPILE );
        /* Draw the front faces */
        glColor3f(1.0, 0.0, 0.0);
        glBegin( GL_POLYGON );
            glVertex3f( -10.0, 30.0, 8.0 );
            glVertex3f( -10.0,-50.0, 8.0 );
            glVertex3f(  10.0,-50.0, 8.0 );
            glVertex3f(  10.0, 30.0, 8.0 );
        glEnd( );
        glBegin( GL_POLYGON );
            glVertex3f( -37.5, 50.0, 12.5 );
            glVertex3f( -37.5, 30.0, 12.5 );
            glVertex3f(  37.5, 30.0, 12.5 );
            glVertex3f(  37.5, 50.0, 12.5 );
        glEnd( );

        /* Draw the back faces */
        glColor3f(0.0, 1.0, 0.0);
        glBegin( GL_POLYGON );
            glVertex3f(  10.0, 30.0,-8.0 );
            glVertex3f(  10.0,-50.0,-8.0 );
            glVertex3f( -10.0,-50.0,-8.0 );
            glVertex3f( -10.0, 30.0,-8.0 );
        glEnd( );
        glBegin( GL_POLYGON );
            glVertex3f(  37.5, 50.0,-12.5 );
            glVertex3f(  37.5, 30.0,-12.5 );
            glVertex3f( -37.5, 30.0,-12.5 );
            glVertex3f( -37.5, 50.0,-12.5 );
        glEnd( );

        /* Draw the Top of the T */
        glColor3f(0.0, 0.0, 1.0);
        glBegin( GL_QUAD_STRIP );
            glVertex3f( -37.5, 30.0,-12.5 );
            glVertex3f( -37.5, 30.0, 12.5 );
            glVertex3f( -37.5, 50.0,-12.5 );
            glVertex3f( -37.5, 50.0, 12.5 );
            glVertex3f(  37.5, 50.0,-12.5 );
            glVertex3f(  37.5, 50.0, 12.5 );
            glVertex3f(  37.5, 30.0,-12.5 );
            glVertex3f(  37.5, 30.0, 12.5 );
        glEnd( );

        /* Draw the Bottom of the T */
        glColor3f(0.0, 0.0, 1.0);
        glBegin( GL_QUAD_STRIP );
            glVertex3f(  10.0, 30.0,-8.0 );
            glVertex3f(  10.0, 30.0, 8.0 );
            glVertex3f(  10.0,-50.0,-8.0 );
            glVertex3f(  10.0,-50.0, 8.0 );
            glVertex3f( -10.0,-50.0,-8.0 );
            glVertex3f( -10.0,-50.0, 8.0 );
            glVertex3f( -10.0, 30.0,-8.0 );
            glVertex3f( -10.0, 30.0, 8.0 );
        glEnd( );

        /* Draw the Underside of the T */
        glColor3f(0.0, 0.0, 1.0);
        glBegin( GL_QUAD_STRIP );
            glVertex3f( -37.5, 30.0,-12.5 );
            glVertex3f( -10.0, 30.0,-8.0 );
            glVertex3f( -37.5, 30.0, 12.5 );
            glVertex3f( -10.0, 30.0, 8.0 );
            glVertex3f(  37.5, 30.0, 12.5 );
            glVertex3f(  10.0, 30.0, 8.0 );
            glVertex3f(  37.5, 30.0,-12.5 );
            glVertex3f(  10.0, 30.0,-8.0 );
            glVertex3f( -37.5, 30.0,-12.5 );
            glVertex3f( -10.0, 30.0,-8.0 );
        glEnd( );
    /* End the List */
    glEndList( );
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
 *  The Draw function is the main loop for the Graphics process. Draws each
 *  viewport and the lines within them
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
