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

#define NUM_LISTS 2

/* Figure out what this is for, yo */
#define N 1

#define BUF_SIZ 256

#define DEFAULT_FONT GLUT_BITMAP_8_BY_13


/*-----------------------------------------------------------------------------
 *  Global Definitions
 *-----------------------------------------------------------------------------*/
int xmin = -10;
int xmax = 10;
int ymin = -10;
int ymax = 10;


/*-----------------------------------------------------------------------------
 *  Function Definitions
 *-----------------------------------------------------------------------------*/
void Draw( void );
void Keyboard( unsigned char , int , int );
void Reshape( int, int );
void ClearMemory( void );
void DrawText( float, float, void*, char* );
void InitShapes( void );
void ProcessHits( GLint, GLuint[] );
void DrawShapes( GLenum );
void Mouse( int, int, int, int );

/*-----------------------------------------------------------------------------
 *  Main Function
 *  Initiates the graphics buffer, creates the window
 *-----------------------------------------------------------------------------*/
int main( int argc, char *argv[] )
{
    /* Seed the random number generator */
    srand(time(0));

    /* Initialize the drawing environment */
    glutInit( &argc, argv );

    /* Initialize the display mode */
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE );

    /* Create an application window of a certain size */
    glutInitWindowSize( 850, 450 );

    /* Create an application window on the screen */
    glutCreateWindow( "Assignment #n: An Assignment" );

    /* Register the function that does drawing */
    glutDisplayFunc( Draw );

    /* Create the Keyboard callback */
    glutKeyboardFunc( Keyboard );

    /* Create the Mouse callback */
    glutMouseFunc( Mouse );

    /* Create the Reshape callback */
    glutReshapeFunc( Reshape );

    /* Enable GL Properties */
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    /* Register Exit Handler */
    atexit(ClearMemory);

    /* Initialize the House Shapes */
    InitShapes( );

    /* Turn over control to OpenGL */
    glutMainLoop();

    return( 0 );  /* NOTE: this is here only for ANSI requirements */
}

/*-----------------------------------------------------------------------------
 *  InitShapes
 *  Create the shapes used in the project
 *-----------------------------------------------------------------------------*/
void InitShapes( void )
{
    /* Define the two new lists */
    glNewList( 'h', GL_COMPILE );
        /* Draw the main part of the house */
        glColor3f( 1.0, 0.0, 0.0 );
        glBegin( GL_QUADS );
            glVertex3f(  1.0,  1.0, 0.0 );
            glVertex3f( -1.0,  1.0, 0.0 );
            glVertex3f( -1.0, -1.0, 0.0 );
            glVertex3f(  1.0, -1.0, 0.0 );
        glEnd( );

        /* Draw the top of the house */
        glColor3f( 0.0, 1.0, 0.0 );
        glBegin( GL_TRIANGLES );
            glVertex3f(  1.25,  1.0, 0.0 );
            glVertex3f(   0.0,  2.0, 0.0 );
            glVertex3f( -1.25,  1.0, 0.0 );
        glEnd( );
    glEndList( );
}

/*-----------------------------------------------------------------------------
 *  ClearMemory
 *  Clears the dynamically allocated memory at close
 *-----------------------------------------------------------------------------*/
void ClearMemory( void )
{
}

/*-----------------------------------------------------------------------------
 *  Draw
 *  The Draw function is the main loop for the Graphics process. Draws each
 *  viewport and the lines within them
 *-----------------------------------------------------------------------------*/
void Draw( void )
{
    char buf[BUF_SIZ];

    /* Clear the screen ... */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity( );

    /* Draw some text */
    sprintf(buf, "Some text");
    DrawText( -0.5, 2.5, DEFAULT_FONT, buf);

    /* Render the Shape */
    DrawShapes( GL_RENDER );

    /* Flush the buffer */
    glutSwapBuffers();

    return;
}

/*-----------------------------------------------------------------------------
 *  Keyboard
 *  Handles the keyboard input for each of the various buttons
 *-----------------------------------------------------------------------------*/
void DrawShapes( GLenum mode )
{
    /* Render the Shape */
    glLoadName(1);
    glCallList('h');

    /* Render the Shape */
    glPushMatrix();
        glLoadName(2);

        glTranslatef( 5.0, 5.0, 0.0 );
        glCallList( 'h' );
    glPopMatrix();
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
        case 27: /* Escape the Program */
            exit(0);
            break;
        default: return; /* Exit if another key was pressed */
    }

    /* Redraw the Display */
    glutPostRedisplay();
}

/*-----------------------------------------------------------------------------
 *  Mouse
 *  Handles Mouse Movement and Selection
 *-----------------------------------------------------------------------------*/
void Mouse(int button, int state, int x, int y)
{
    GLuint nameBuffer[BUF_SIZ];
    GLint hits;
    GLint viewport[4];

    if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
    {
        /* Get the Viewport and set to Projection */
        glGetIntegerv( GL_VIEWPORT, viewport );
        glMatrixMode( GL_PROJECTION );

        /* Save the Projection matrix */
        glPushMatrix( );
        glLoadIdentity( );
        gluPickMatrix( (GLdouble)x, (GLdouble)(viewport[3] - y),
                N, N, viewport );
        gluOrtho2D( xmin, xmax, ymin, ymax );

        /* Set the Render Mode to the Selection mode */
        glMatrixMode( GL_MODELVIEW );
        glSelectBuffer(BUF_SIZ, nameBuffer);
        glRenderMode( GL_SELECT );

        /* Initialize the Object Naming */
        glInitNames( );
        glPushName( 0 );

        /* Draw the Shapes with Select enabled */
        DrawShapes( GL_SELECT );

        /* Reset the Projection Matrix */
        glMatrixMode( GL_PROJECTION );
        glPopMatrix( );

        /* Return drawing to ModelView */
        glMatrixMode( GL_MODELVIEW );

        /* Get the number of hits */
        hits = glRenderMode( GL_RENDER );
        ProcessHits( hits, nameBuffer );

        /* Draw the display */
        glutPostRedisplay( );
    }
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
    gluOrtho2D( xmin, xmax, ymin, ymax );

    /* Change to ModelView Matrix */
    glMatrixMode( GL_MODELVIEW );
}

/*-----------------------------------------------------------------------------
 *  DrawText
 *  Draws a set of text using the GLUT bitmap String for a location at x and
 *  y for a set font and buf
 *-----------------------------------------------------------------------------*/
void DrawText( float x, float y, void* font, char* buf) 
{
    /* Set the position */
    glRasterPos2f(x, y);

    /* Print the text */
    glutBitmapString(font, buf);
}

/*-----------------------------------------------------------------------------
 *  ProcessHits
 *  Processes which items have been clicked
 *-----------------------------------------------------------------------------*/
void ProcessHits( GLint hits, GLuint buffer[] ) 
{
    unsigned int i, j;
    GLuint names, *ptr;

    printf("hits = %d\n", hits);
    ptr = buffer;

    printf("names: %d %d %d %d\n", buffer[0], buffer[1], buffer[2], buffer[3]);

    for(i = 0; i < hits; ++i)
    {
        names = *ptr;

        /* Skip over number of names and depths */
        ptr += 3;

        /* Check each name in the records */
        for(j = 0; j < names; ++j)
        {
            if(*ptr == 1) printf("Red Rectangle\n");
            else printf("Blue Rectangle\n");

            /* Go to the next hit record */
            ptr++;
        }
    }
}
