/*
 * =====================================================================================
 *
 *       Filename:  Thompson_01_8263.c
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
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0

#define DEFAULT_FONT GLUT_BITMAP_8_BY_13
#define BUF_SIZ 256

/*-----------------------------------------------------------------------------
 *  Function Definitions
 *-----------------------------------------------------------------------------*/
void Draw( void );
void DrawLine( float , float , float, float );
void KeyboardFunc( unsigned char , int , int );
void DrawText( float x, float y, void* font, char* buf);
void ClearMemory( void );

/*-----------------------------------------------------------------------------
 *  Main Function
 *  Initiates the graphics buffer, creates the window and CalculatePoints
 *-----------------------------------------------------------------------------*/
int main( int argc, char *argv[] )
{
    /* Seed the random number generator */
    srand(time(0));

    /* Initialize the drawing environment */
    glutInit( &argc, argv );

    /* Initialize the display mode */
    glutInitDisplayMode ( GLUT_DOUBLE );

    /* Create an application window of a certain size */
    glutInitWindowSize( 850, 450 );

    /* Create an application window on the screen */
    glutCreateWindow( "Assignment #2: 3D Letter" );

    /* Register the function that does drawing */
    glutDisplayFunc( Draw );

    /* Create the Keyboard callback */
    glutKeyboardFunc( KeyboardFunc );

    /* Register Exit Handler */
    atexit(ClearMemory);

    /* Turn over control to OpenGL */
    glutMainLoop();

    return( 0 );  /* NOTE: this is here only for ANSI requirements */
}


/*-----------------------------------------------------------------------------
 *  ClearMemory
 *  Clears the dynamically allocated memory at close
 *-----------------------------------------------------------------------------*/
void ClearMemory( void )
{
    /* Clear dynamically allocated memory */
}


/*-----------------------------------------------------------------------------
 *  Draw
 *  The Draw function is the main loop for the Graphics process. Draws each
 *  viewport and the lines within them
 *-----------------------------------------------------------------------------*/
void Draw( void )
{
    char buf[BUF_SIZ];
    int i;
    int starCount = 0;

    /* Clear the screen ... */
    glClear( GL_COLOR_BUFFER_BIT );

    /* Resize the viewport */
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH) * 0.7,
                     glutGet(GLUT_WINDOW_HEIGHT));

    /* Draw the Front Face */
    glBegin( GL_POLYGON );
        glVertex3f( -37.5, 50.0, 12.5 );
        glVertex3f( -37.5, 30.0, 12.5 );
        glVertex3f( -10.0, 30.0, 12.5 );
        glVertex3f( -10.0,-50.0, 12.5 );
        glVertex3f(  10.0,-50.0, 12.5 );
        glVertex3f(  10.0, 30.0, 12.5 );
        glVertex3f(  37.5, 30.0, 12.5 );
        glVertex3f(  37.5, 50.0, 12.5 );
    glEnd( );

    /* Draw the Back Face */
    glBegin( GL_POLYGON );
        glVertex3f(  37.5, 50.0,-12.5 );
        glVertex3f(  37.5, 30.0,-12.5 );
        glVertex3f(  10.0, 30.0,-12.5 );
        glVertex3f(  10.0,-50.0,-12.5 );
        glVertex3f( -10.0,-50.0,-12.5 );
        glVertex3f( -10.0, 30.0,-12.5 );
        glVertex3f( -37.5, 30.0,-12.5 );
        glVertex3f( -37.5, 50.0,-12.5 );
    glEnd( );

    /* Draw the Inner Sides */
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
    glEnd( );

    /* Flush the buffer */
    glutSwapBuffers( ); 

    return;
}

/*-----------------------------------------------------------------------------
 *  KeyboardFunc
 *  Handles the keyboard input for each of the various buttons
 *-----------------------------------------------------------------------------*/
void KeyboardFunc( unsigned char key, int x, int y )
{
    /* Determine which key is pressed */
    switch(key)
    {
        default: return; /* Exit if another key was pressed */
    }

    /* Redraw the Display */
    glutPostRedisplay();
}


/*-----------------------------------------------------------------------------
 *  DrawLine
 *  Draws a line at two given points
 *-----------------------------------------------------------------------------*/
void DrawLine( float x0, float y0, 
               float x1, float y1 )
{
    /* Draw a line  */
    glBegin( GL_LINES );
        glVertex2f( x0, y0 );
        glVertex2f( x1, y1 );
    glEnd();

    return;
}

/*-----------------------------------------------------------------------------
 *  DrawText
 *  Draws a set of text using the GLUT bitmap String for a location at x and
 *  y for a set font and buf
 *-----------------------------------------------------------------------------*/
void DrawText( float x, float y, void* font, char* buf) 
{
    /* Set the color */
    glColor3f(0.0, 0.7, 0.0);

    /* Set the position */
    glRasterPos2f(x, y);

    /* Print the text */
    glutBitmapString(font, buf);
}
