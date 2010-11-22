/* PROGRAM:  q.c
   AUTHOR:   Carolina Ayala, Cody Thompson
   DATE:     Nov 1st 2010   
   PURPOSE:  Coding question in Midterm
*/

/**************************************************************************/
/* Include necessary header files
 **************************************************************************/
#include <GL/glut.h>     
#include <GL/gl.h>
#include <GL/glu.h>     
#include <unistd.h>     
#include <stdlib.h>     
#include <math.h>

/**************************************************************************/
/* Declare needed defines
 **************************************************************************/
#define ESCAPE 27       // Ascii code for the escape key
#define DELTA_ANGLE 5.0
#define X 0
#define Y 1
#define Z 2

/**************************************************************************/
/* Declare needed global variables
 **************************************************************************/
static GLint window;                // Our window
static GLint Window_Width  = 500;   // Initial (& on-going) window width
static GLint Window_Height = 500;   // Initial (& on-going) window height
static GLfloat  rotY = 0.0;         // Rotation in the Y
static GLfloat  rotX = 0.0;         // Rotation in the X
static GLenum mode = GL_FILL;       // How to draw the polygons
int cubelist;

/*
 * Square centred in ( 0, 0, 0 ) 
 */
GLfloat thinRectangle[][3] = {{ -0.5, -0, 1.0 },    { 0.5, -0, 1.0 },
                         {  0.5,  3, 1.0 },    {-0.5,  3, 1.0 } };
GLfloat thickRectangle[][3] = {{ -1, -0, 1.0 },    { 1, -0, 1.0 },
                         {  1,  3, 1.0 },    {-1,  3, 1.0 } };
/**************************************************************************/
/* Declare function prototypes
 **************************************************************************/
void Init( void );
void Draw( void );
void DrawThinSquare( void );
void DrawThickSquare( void );
void DrawTriangle( void );
void DrawCoordinates( void );
void DrawEllipse( void );
void DrawCircle( int r, int sides );
void DrawPolygon( int a, int b, int c, int d );
void keyPressed( unsigned char key, int x, int y);
void MousePressed ( int button, int state, int mouseX, int mouseY );
void ReshapeWindow( int w, int h );
void SpecialKey( int key, int x, int y);

/**************************************************************************/
/* main: all initialization and callback registration.
 **************************************************************************/
int main(int argc, char **argv) 
{  

  /* All of this functions should be already known */
  glutInit( &argc, argv );  

  /* Display set to  be able to recognize RGBA colours, double buffers and depths */
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH ); 
  glutInitWindowSize( Window_Width, Window_Height );
  glutInitWindowPosition( 0, 0 );  
  window = glutCreateWindow( "10F MIDTERM CST8236" );
  glutDisplayFunc( Draw );  
  glutReshapeFunc( ReshapeWindow );
  Init();
  /* Start Event Processing Engine */  
  glutMainLoop();  

  return 1;
}

/**************************************************************************/
/* A init function which handles the window initialization 
 **************************************************************************/
void Init( void )               
{
   glClearColor (0.25, 0.25, 0.25, 0.0);
   glClearDepth(1.0);           
   glEnable( GL_DEPTH_TEST );    
   glEnable( GL_CULL_FACE );

}

/**************************************************************************/
/* A reshape function which handles the resize of the window 
 **************************************************************************/
void ReshapeWindow(int Width, int Height)
{
  glViewport( 0, 0, Width, Height );
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho( -10, 10, -10, 10, -10, 10 ); 
  glMatrixMode(GL_MODELVIEW);

}

/**************************************************************************/
/* A function that actually draw 
 **************************************************************************/
void Draw()
{

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();

    DrawCoordinates();

    glColor3f( 0.0, 0.0, 1.0 );
    glPolygonMode( GL_FRONT,  GL_LINE );    

    /* Draw a Thick Rectangle */
    DrawThickSquare();

    glTranslatef(0, 4, 0);

    /* Draw a Circle */
    DrawCircle(1, 100);

    /* Position ourselves for next two shapes */
    glRotatef(45, 0, 0, 1);
    glTranslatef(0, 1, 0);

    glPushMatrix();
        /* Draw the Ellipse */
        glRotatef(30, 0, 0, 1);
        DrawEllipse();
    glPopMatrix();

    /* Draw the Thin Rectangle */
    glRotatef(-30, 0, 0, 1);
    DrawThinSquare();

    /* Draw the Triangle */
    glTranslatef(0, 3, 0);
    glRotatef(100, 0, 0, 1);
    DrawTriangle();


    glutSwapBuffers();
}

/**************************************************************************/
/* A function that draws a polygon with vertices a b c d 
 **************************************************************************/
void DrawCircle( int r, int sides ) {
        float inc = (2 * M_PI / sides);
        float i = 0.0f;

        glBegin( GL_POLYGON );
            for(i = 0; i <= 2 * M_PI; i += inc)
                glVertex3f(r * cos(i), r * sin(i), 1.0);
        glEnd();
}
/**************************************************************************/
/* A function that draws a cube
 **************************************************************************/
void DrawThickSquare( void )
{
    glBegin( GL_QUADS );
        glVertex3fv( thickRectangle[0] );
        glVertex3fv( thickRectangle[1] );
        glVertex3fv( thickRectangle[2] );
        glVertex3fv( thickRectangle[3] );
    glEnd();
}
void DrawThinSquare( void )
{
    glBegin( GL_QUADS );
        glVertex3fv( thinRectangle[0] );
        glVertex3fv( thinRectangle[1] );
        glVertex3fv( thinRectangle[2] );
        glVertex3fv( thinRectangle[3] );
    glEnd();
}
void DrawEllipse( void )
{
    glBegin( GL_TRIANGLE_FAN );
        glVertex3f( 0, 2, 1 );
        glVertex3f( 0, 4, 1 );
        glVertex3f( -0.25, 3, 1 );
        glVertex3f( -0.5, 2, 1 );
        glVertex3f( -0.25, 1, 1 );
        glVertex3f( 0, 0, 1 );
        glVertex3f( 0, 4, 1 );
    glEnd();
}
void DrawTriangle( void )
{
    glBegin( GL_TRIANGLES );
        glVertex3f( -0.5, 0, 1 );
        glVertex3f( 0.5, 0, 1 );
        glVertex3f( 0, 3, 1 );
    glEnd();
}
/**************************************************************************/
/* Draws coordinate systems
 **************************************************************************/
void DrawCoordinates( void  ){
  glBegin( GL_LINES );
        glVertex3f( -100,    0.0, 0.0);
        glVertex3f(  100,    0.0, 0.0);
        glVertex3f(    0, -100.0, 0.0);
        glVertex3f(    0,  100.0, 0.0);
  glEnd();
}
