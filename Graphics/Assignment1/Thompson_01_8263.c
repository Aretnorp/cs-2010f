/*
 * =====================================================================================
 *
 *       Filename:  star.c
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

#define MAX_INT 72
#define MIN_INT 2

#define POINT_SIZE 4.5

#define RADIUS 0.8


/*-----------------------------------------------------------------------------
 *  Structure Definitions
 *-----------------------------------------------------------------------------*/
struct Point
{
    float x;
    float y;
};


/*-----------------------------------------------------------------------------
 *  Function Definitions
 *-----------------------------------------------------------------------------*/
void Draw( void );
void DrawLine( float , float , float, float );
void KeyboardFunc( unsigned char , int , int );
void CalculatePoints( float r, int m, int n );
void DrawPolygon( float r, int sides );
void DrawStarPoints( struct Point *p, int m );
void DrawStarPolygon( struct Point *p, int m, int n );
void DrawText( float x, float y, void* font, char* buf);
void ClearMemory( void );

int enableAll = FALSE;
int enableShow = FALSE;
int enableRandom = FALSE;

int m = 7;
int n = 3;

struct Point *p;


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
    glutCreateWindow( "Assignment #1: Star Polygon" );

    /* Register the function that does drawing */
    glutDisplayFunc( Draw );

    /* Create the Keyboard callback */
    glutKeyboardFunc( KeyboardFunc );

    /* Register Exit Handler */
    atexit(ClearMemory);

    /* Calculate the Points */
    CalculatePoints(RADIUS, m, n);

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
    free(p);
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

/* Enable smoothing (not multisampling sadly) */
glEnable( GL_BLEND );
    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_POINT_SMOOTH );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    /* Resize the viewport */
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH) * 0.7,
                     glutGet(GLUT_WINDOW_HEIGHT));

    /* Draw the Star Polygons */
    if(enableAll)
    {
        /* Draw all the Star Polygons */
        for(i = 1; i < n; ++i)
            if((n <= (m / 2)) && (CalculatePrime(m, i) == 1))
            {
                DrawStarPolygon(p, m, i);
                starCount++;
            }
    }

    /* Draw a Star Polygon */
    if(((n <= (m / 2)) && CalculatePrime(m, n) == 1))
    {
        DrawStarPolygon(p, m, n);
        starCount++;
    }
    else
        /* Issue Text regarding Polygon */
        DrawText(-0.8, -0.9, DEFAULT_FONT, "Star Polygon can not be drawn!");

    /* Draw the additional objects */
    if(enableShow)
    {
        /* Draw the Cartesian plane */
        DrawLine(-1.0, 0.0, 1.0, 0.0);
        DrawLine(0.0, -1.0, 0.0, 1.0);

        /* Draw the Circle */
        glColor3f(0.8, 0.8, 0.8);
        DrawPolygon(RADIUS, 100);
        
        /* Draw the Points */
        DrawStarPoints(p, m);
    }

    /* Draw the ViewPort */
    glViewport(glutGet(GLUT_WINDOW_WIDTH) * 0.7, 0,
               glutGet(GLUT_WINDOW_WIDTH) * 0.3, glutGet(GLUT_WINDOW_HEIGHT));

    /* Draw the Background */
    glBegin(GL_QUADS);
        glColor3f(0.22, 0.22, 0.22);
        glVertex2f(-1.0, -1.0);
        glVertex2f(-1.0, 1.0);
        glVertex2f(1.0, 1.0);
        glVertex2f(1.0, -1.0);
    glEnd();

    /* Draw the Title */
    DrawText(-0.5, 0.9, DEFAULT_FONT, "My Star Polygon");

    /* Draw the Title Line */
    glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(-0.8, 0.85);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0.8, 0.85);
    glEnd();

    /* Draw the M value */
    sprintf(buf, "[Mm] m value: %d", m);
    DrawText(-0.8, 0.7, DEFAULT_FONT, buf);

    /* Draw the N value */
    sprintf(buf, "[Nn] n value: %d", n);
    DrawText(-0.8, 0.6, DEFAULT_FONT, buf);

    /* Draw the Show All */
    sprintf(buf, "[%c] Show All Polygons    [a]", enableAll ? 'x' : ' ');
    DrawText(-0.8, 0.4, DEFAULT_FONT, buf);

    /* Draw the Show Additional */
    sprintf(buf, "[%c] Show Graph           [s]", enableShow ? 'x' : ' ');
    DrawText(-0.8, 0.3, DEFAULT_FONT, buf);

    /* Draw the Show Random Colors */
    sprintf(buf, "[%c] Show Random Colors   [r]", enableRandom ? 'x' : ' ');
    DrawText(-0.8, 0.2, DEFAULT_FONT, buf);

    /* Draw the Polygon Count */
    if(starCount == 0)
        DrawText(-0.8, 0.0, DEFAULT_FONT, "NO STAR POLYGONS");
    else
    {
        sprintf(buf, "%d Star Polygon(s)", starCount);
        DrawText(-0.8, 0.0, DEFAULT_FONT, buf);
    }

    /* Flush the buffer */
    glutSwapBuffers(); 

    return;
}


/*-----------------------------------------------------------------------------
 *  CalculatePoints
 *  Calculates the Points around a given r for a given m and n. Splits a
 *  circle into a used radius. Used with a StarPolygon algorithm.
 *-----------------------------------------------------------------------------*/
void CalculatePoints( float r, int m, int n )
{
    float angle;
    int i = 0;

    /* Clear the current memory */
    free(p);

    /* Instantiate the new array of Points */
    p = (struct Point*)malloc(sizeof(struct Point) * m);
    if(p == NULL)
    {
        /* Error encountered */
        fprintf(stderr, "Could not allocate array\n");
        exit(0);
    }

    /* Calculate the Points */
    angle = ( 2 * M_PI ) / m;
    for(i = 0; i < m; ++i)
    {
        p[i].x = cos(angle * i) * r;
        p[i].y = sin(angle * i) * r;
    }
}


/*-----------------------------------------------------------------------------
 *  DrawStarPolygon
 *  Creates a StarPolygon using a given arrays of Points for m sides and
 *  n divisions
 *-----------------------------------------------------------------------------*/
void DrawStarPolygon( struct Point *p, int m, int n )
{
    int i, j;

    /* Set the Default Color */
    glColor3f(0.5, 0.5, 0.5);

    /* Begin drawing a Strip of Lines */
    glBegin( GL_LINE_STRIP );
    {
        for(i = 0; i <= m; ++i)
        {
            /* Draw Random Colors if required */
            if(enableRandom)
                glColor3f(((float)rand() / RAND_MAX),
                        ((float)rand() / RAND_MAX),
                        ((float)rand() / RAND_MAX));

            /* Calculate the next point */
            j = (i * n) % m;

            /* Setup the point */
            glVertex2f(p[j].x, p[j].y);
        }
    }
    glEnd();
}


/*-----------------------------------------------------------------------------
 *  DrawStarPoints
 *  Draws each vertex based on the provided struct point P
 *-----------------------------------------------------------------------------*/
void DrawStarPoints( struct Point *p, int m )
{
    int i = 0;

    /* Set the Point Size */
    glPointSize(POINT_SIZE);

    /* Set the Point Color */
    glColor3f(1.0, 0.0, 0.0);

    /* Draw the Points */
    glBegin( GL_POINTS );
    {
        /* Calculate out the angles */
        for(i = 0; i < m; ++i)
            glVertex2f(p[i].x, p[i].y);
    }
    glEnd();
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
        case 'r': /* Enable the Show Random Colors */
            if(enableRandom)
                enableRandom = FALSE;
            else
                enableRandom = TRUE;
            break;
        case 'M':
            if(m < MAX_INT)
                m++; /* Increment m */
            break;
        case 'm':
            if(m > MIN_INT)
            {
               m--; /* Decrement m */
               if(n >= (m / 2))
                   n = (m / 2); /* Set n */
            }
            break;
        case 'N':
            if(n < (m / 2))
                n++; /* Increment n */
            break;
        case 'n':
            if(n > MIN_INT)
                n--; /* Decrement n */
            break;
        default: return; /* Exit if another key was pressed */
    }
    /* Recalculate Points */
    CalculatePoints(RADIUS, m, n);

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
    glColor3f(0.75, 0.75, 0.75);
    glBegin( GL_LINES );
        glVertex2f( x0, y0 );
        glVertex2f( x1, y1 );
    glEnd();

    return;
}


/*-----------------------------------------------------------------------------
 *  DrawPolygon
 *  Draws a polygon with a given sides and radius
 *-----------------------------------------------------------------------------*/
void DrawPolygon( float r, int sides ) 
{
    float inc = (2 * M_PI / sides);
    float i = 0.0f;

    /* Draw a line  */
    glColor3f(1.0, 1.0, 1.0);
    glBegin( GL_LINE_LOOP );
        for(i = 0; i <= 2 * M_PI; i += inc)
            glVertex2f(r * cos(i), r * sin(i));
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


/*-----------------------------------------------------------------------------
 *  CalculatePrime
 *  Calculates the coprime number between m and n using Eucidlean algorithm
 *-----------------------------------------------------------------------------*/
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
