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
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0

#define DEFAULT_FONT GLUT_BITMAP_8_BY_13
#define BUF_SIZ 256

#define MAX_INT 50
#define MIN_INT 0

#define POINT_SIZE 4.5

/**************************************************************************/
/* Declare function prototypes
 **************************************************************************/
struct Point
{
    float x;
    float y;
};

/**************************************************************************/
/* Declare function prototypes
 **************************************************************************/
void Draw( void );
void DrawLine( float , float , float, float );  /* Draws a line */
void KeyboardFunc( unsigned char , int , int ); /* Handles Keyboard */

int enableAll = FALSE;
int enableShow = FALSE;
int enableRandom = FALSE;

int m = 7;
int n = 3;

struct Point *p;

/**************************************************************************/
/* main: all initialization and callback registration.
 **************************************************************************/
int main( int argc, char *argv[] )
{
    /* Seed the random number generator */
    srand(time(0));

    /* Initialize the drawing environment */
    glutInit( &argc, argv );

    /* Initialize the display mode */
    glutInitDisplayMode ( GLUT_DOUBLE );

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

void CalculatePoints( float r, int m, int n )
{
    float angle;
    int i = 0;

    /* Clear the current memory */
    free(p);

    /* Instantiate the new array of Points */
    if((p = malloc(sizeof(struct Point) * m)) == NULL)
    {
        /* Error encountered */
        fprintf(stderr, "Could not allocate array\n");
        exit(0);
    }

    /* Calculate the Points */
    angle = ( 2 * M_PI ) / m;
    for(i = 0; i < m; ++i)
    {
        p[i].x = cos(angle * i);
        p[i].y = sin(angle * i);
    }
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
                m--; /* Decrement m */
            break;
        case 'N':
            if(n < MAX_INT)
                n++; /* Increment n */
            break;
        case 'n':
            if(n > MIN_INT)
                n--; /* Decrement n */
            break;
        default: return; /* Exit if another key was pressed */
    }

    /* Redraw the Display */
    glutPostRedisplay();
}

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
        glColor3f(1.0, 1.0, 1.0);
        float angle = ( 2 * M_PI ) / m;
        for(i = 0; i < m; ++i)
        {   
            if(enableRandom)
                glColor3f(((float)rand() / RAND_MAX),
                        ((float)rand() / RAND_MAX),
                        ((float)rand() / RAND_MAX));
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

    /* Set the Point Size */
    glPointSize(POINT_SIZE);

    /* Draw the Points */
    glBegin( GL_POINTS );
    { 
        /* Calculate out the angles */
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

void DrawText( float x, float y, void* font, char* buf) 
{
    /* Set the color */
    glColor3f(1.0, 1.0, 1.0);

    /* Set the position */
    glRasterPos2f(x, y);

    /* Print the text */
    glutBitmapString(font, buf);
}

void Draw( void )
{
    char buf[BUF_SIZ];
    int menu;
    int i;
    float r = 0.8;
    int starCount = 0;

    /* Clear the screen ... */
    glClear( GL_COLOR_BUFFER_BIT );

    /* Resize the viewport */
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH) - (glutGet(GLUT_WINDOW_WIDTH) * 0.3), 
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
            glColor3f(0.75, 0.75, 0.75);
            DrawLine(-1.0, 0.0, 1.0, 0.0);
            DrawLine(0.0, -1.0, 0.0, 1.0);

            /* Draw the Circle */
            glColor3f(0.8, 0.8, 0.8);
            DrawPolygon(r, 100);
            
            /* Draw the Points */
            DrawStarPoints(r, m, n);
        }

    }
    else
    {
        /* Issue Text regarding Polygon */
        DrawText(-0.5, -0.75, DEFAULT_FONT, "Star Polygon can not be drawn!");
    }

    /* Draw the ViewPort */
    glViewport(glutGet(GLUT_WINDOW_WIDTH) - (glutGet(GLUT_WINDOW_WIDTH) * 0.3), 0,
               glutGet(GLUT_WINDOW_WIDTH) * 0.3, glutGet(GLUT_WINDOW_HEIGHT));

    /* Draw the Background */
    glBegin(GL_QUADS);
        glColor3f(0.22, 0.22, 0.22);
        glVertex2f(-1.0, -1.0);
        glVertex2f(-1.0, 1.0);
        glVertex2f(1.0, 1.0);
        glVertex2f(1.0, -1.0);
    glEnd();

    /* Draw the M value */
    sprintf(buf, "[M/m] m value: %d", m);
    DrawText(-0.8, 0.8, DEFAULT_FONT, buf);

    /* Draw the N value */
    sprintf(buf, "[N/n] n value: %d", n);
    DrawText(-0.8, 0.7, DEFAULT_FONT, buf);

    /* Draw the Show All */
    sprintf(buf, "[%c] Show All", enableAll ? 'x' : ' ');
    DrawText(-0.8, 0.6, DEFAULT_FONT, buf);

    /* Draw the Show Additional */
    sprintf(buf, "[%c] Show Graph", enableShow ? 'x' : ' ');
    DrawText(-0.8, 0.5, DEFAULT_FONT, buf);

    /* Draw the Show Random Colors */
    sprintf(buf, "[%c] Show Random Colors", enableRandom ? 'x' : ' ');
    DrawText(-0.8, 0.4, DEFAULT_FONT, buf);

    /* Flush the buffer */
    glutSwapBuffers(); 

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
