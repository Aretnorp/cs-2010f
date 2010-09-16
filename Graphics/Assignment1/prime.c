/* PROGRAM:  line.c 
   AUTHOR:   Michael Anderson
         Carolina Ayala 
   MODIFIED BY: Cody Thompson
   DATE:     13/09/10
   PURPOSE:  Basic program in OpenGL 
   LEVEL DIFFICULTY: Lab was easy (given)
   OBJECTIVES: Familiarize yourself with OpenGL and GLUT
*/
/**************************************************************************/
/* Include necessary header files
 **************************************************************************/
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

/**************************************************************************/
/* Declare function prototypes
 **************************************************************************/
void Draw( void );
void DrawLine( float , float , float, float );  /* Draws a line */
void KeyboardFunc( unsigned char , int , int ); /* Handles Keyboard */

int enableAll = FALSE;
int enableShow = FALSE;

void MenuTest(int menu)
{
    return;
}

/**************************************************************************/
/* main: all initialization and callback registration.
 **************************************************************************/
int main( int argc, char *argv[] )
{
    /* Initialize the drawing environment */
    glutInit( &argc, argv );

    /* Create an application window of a certain size */
    glutInitWindowSize( 600, 300 );

    /* Create an application window on the screen */
    glutCreateWindow( "Assignment #1: Star Polygon" );

    /* Register the function that does drawing */
    glutDisplayFunc( Draw );

    /* Create the Keyboard callback */
    glutKeyboardFunc( KeyboardFunc );
  
    /* Turn over control to OpenGL */
    glutMainLoop();

    return( 0 );  /* NOTE: this is here only for ANSI requirements */
}

void KeyboardFunc( unsigned char key, int x, int y )
{
    /* Determine which key is pressed */
    switch(key)
    {
        case 27: /* Escape the Program */
            exit(0);
            break;
        case 's': /* Enable the Show Display Items */
            if(enableShow)
                enableShow = FALSE;
            else
                enableShow = TRUE;
            break;
        case 'a': /* Enable the Show All Polygons */
            if(enableAll)
                enableAll = FALSE;
            else
                enableAll = TRUE;
            break;
    }

    /* Redraw the Display */
    glutPostRedisplay();

    return;
}

/**************************************************************************/
/* A function which draws a line 
 **************************************************************************/
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

void DrawPolygon( float r, int sides ) 
{
    float inc = (2 * M_PI / sides);
    float i = 0.0f;

    /* Draw a line  */
    glBegin( GL_LINE_LOOP );
        for(i = 0; i <= 2 * M_PI; i += inc)
            glVertex2f(r * cos(i), r * sin(i));
    glEnd();

    return;
}

void DrawStarPolygon( float r, int m, int n )
{
    int i = 0;

    glBegin( GL_LINE_STRIP );
    { 
        float angle = ( 2 * M_PI ) / m;
        for(i = 0; i < m; ++i)
        {   
            glVertex2f(cos(angle * ( i * n )) * r, 
                       sin(angle * ( i * n )) * r);
            glVertex2f(cos(angle * ( (i + 1) * n) ) * r,
                       sin(angle * ( (i + 1) * n) ) * r); 
        }
    }   
    glEnd();
}

void DrawStarPoints( float r, int m, int n )
{
    int i = 0;

    glBegin( GL_POINTS );
    { 
        float angle = ( 2 * M_PI ) / m;
        for(i = 0; i < m; ++i)
        {   
            glVertex2f(cos(angle * ( i * n )) * r, 
                       sin(angle * ( i * n )) * r);
            glVertex2f(cos(angle * ( (i + 1) * n) ) * r,
                       sin(angle * ( (i + 1) * n) ) * r); 
        }
    }   
    glEnd();
}

void Draw( void )
{
    int menu;
    int i;
    int m = 7;
    int n = 3;
    float r = 0.8;

  	/* Clear the screen ... */
   	glClear( GL_COLOR_BUFFER_BIT );

    /* Resize the viewport */
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH) - 100, 
                     glutGet(GLUT_WINDOW_HEIGHT));

	/* Determine if to draw the Star Polygon */
    if((CalculatePrime(m, n) == 1) && (n <= (m / 2)))
    {
        /* Draw the Star Polyon */
        if(enableAll)
        {
            /* Draw all the Star Polygons */
            for(i = 1; i <= n; ++i)
                if(CalculatePrime(m, n) == 1)
                    DrawStarPolygon(r, m, i);
        }
        else
        {
            /* Draw the single Star Polygon */
            DrawStarPolygon(r, m, n);
        }

        /* Draw the additional objects */
        if(enableShow)
        {
            /* Draw the Cartesian plane */
            DrawLine(-1.0, 0.0, 1.0, 0.0);
            DrawLine(0.0, -1.0, 0.0, 1.0);

            /* Draw the Circle */
            DrawPolygon(r, 100);
            
            /* Draw the Points */
            DrawStarPoints(r, m, n);
        }
    }

  	/* Flush the buffer */
  	glFlush(); 
   
   	return;
}

/**************************************************************************/
/* A function which calculates coprime between to ints
 **************************************************************************/
int CalculatePrime(int m, int n)
{
    while(n != 0)
    {
        int t = n;
        n = m % n;
        m = t;
    } 
    return m;
}
