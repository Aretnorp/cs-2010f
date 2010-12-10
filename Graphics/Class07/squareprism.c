/* PROGRAM:  Lighting.c 
   AUTHOR:   Carolina Ayala
   DATE:     20/03/10 
   PURPOSE:  Winter 2010 
             Basic Light concepts 
   NOTE:             
 */

/**************************************************************************/
/* Include necessary header files
 **************************************************************************/
#include <GL/glut.h>     
#include <GL/gl.h>
#include <unistd.h>     
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/**************************************************************************/
/* Declare needed defines
 **************************************************************************/
#define ESCAPE 27       // Ascii code for the escape key
#define DELTA 5.0
#define X 0
#define Y 1
#define Z 2


#define RED 1.0, 0.0, 0.0
#define BLUE 0.0, 0.0, 1.0
#define FONT  GLUT_BITMAP_8_BY_13

#define TITLE "I Love Light"

#define TV0  50.0, -50.0,  100.0
#define TV1  50.0,  50.0,  100.0
#define TV2 -50.0,  50.0,  100.0
#define TV3 -50.0, -50.0,  100.0

#define BV0 -50.0,   0.0, -100.0
#define BV1   0.0,  50.0, -100.0
#define BV2  50.0,   0.0, -100.0
#define BV3   0.0, -50.0, -100.0

/**************************************************************************/
/* Declare needed global variables
 **************************************************************************/

typedef float point3[3];


int window;                // Our window
GLint Window_Width  = 600; // Initial (& on-going) window width
GLint Window_Height = 600; // Initial (& on-going) window height

GLfloat octrot[] = { 0.0, 0.0, 0.0 }; /* Rotations apply to the cube */
GLfloat *vector = octrot;   /* Vector currently bound to keys */    

/**************************************************************************/
/* Declare function prototypes
 **************************************************************************/
void Init( int Width, int Height );
void Draw( void );
void keyPressed( unsigned char key, int x, int y);
void MousePressed ( int button, int state, int mouseX, int mouseY );
void ReshapeWindow( int w, int h );
void SpecialKey( int key, int x, int y);


/**************************************************************************/
/* main: all initialization and callback registration.
 **************************************************************************/
int main(int argc, char **argv)  {

        glutInit( &argc, argv );  

        glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH  );  
        glutInitWindowSize( Window_Width, Window_Height );
        glutInitWindowPosition( 0, 0 );  
        window = glutCreateWindow( TITLE );
        glutDisplayFunc( Draw );  
        glutReshapeFunc( ReshapeWindow );
        glutKeyboardFunc( keyPressed );
        Init(Window_Width, Window_Height);
        glutMainLoop();  

        return 0;
}

/**************************************************************************/
/* A init function which handles the window initialization 
 * You want to place here anything that needs to be called just ONCE
 **************************************************************************/
void Init(int Width, int Height)
{
        GLfloat specular[] = { 0.5f, 0.5f, 0.5f, 0.5f };

        glClearColor(0.25, 0.25, 0.25, 0.0);

        glClearDepth(1.0);
         glEnable( GL_DEPTH_TEST );

        /*
         * Enable if you don't want to see you back faces
         */
        glEnable( GL_CULL_FACE );

        glEnable( GL_LIGHTING );
        glEnable( GL_LIGHT0 );
        glLightfv( GL_LIGHT0, GL_SPECULAR, specular);

}
/**************************************************************************/
/* A reshape function which handles the resize of the window 
 **************************************************************************/
void ReshapeWindow(int Width, int Height)
{

        Window_Width = Width;
        Window_Height = Height;
        glViewport( 0, 0, Window_Width, Window_Height );
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        /*
         * Use an ortho here for now ... will change later on to a perspective
         */
        glOrtho( -200.0, 200.0, -200.0, 200.0, -200.0, 200.0 );
        glMatrixMode(GL_MODELVIEW);

}

/**************************************************************************/
/* A function that actually draw 
 **************************************************************************/
void Draw()
{
        char     *bufPtr;
        GLfloat position[] = { 0.0f, 0.0f, 300.0f, 1.0f };

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glLoadIdentity();

        /* 
         * Please note that we have covered any rotations yet
         * but we need this to be able to see the octahedron
         * from different angles
         * This is set in the MODELVIEW matrix 
         */
        glLightfv( GL_LIGHT0, GL_POSITION, position);
        glPushMatrix( );
            glRotatef( octrot[Y], 1.0, 0.0, 0.0 );
            glRotatef( octrot[X], 0.0, 1.0, 0.0 );      
            glRotatef( octrot[Z], 0.0, 1.0, 0.0 );      


            /* 
            * Draw the octahedron in lines 
            * Just the FRONT faces
            */ 
            // glPolygonMode(  );
            
            /* Draw the top */
            glBegin( GL_QUADS );
                glVertex3f( TV0 );
                glVertex3f( TV1 );
                glVertex3f( TV2 );
                glVertex3f( TV3 );
            glEnd( );
            glBegin( GL_QUADS );
                glVertex3f( BV0 );
                glVertex3f( BV1 );
                glVertex3f( BV2 );
                glVertex3f( BV3 );
            glEnd( );

            glBegin( GL_TRIANGLE_STRIP );
                glVertex3f( BV0 );
                glVertex3f( TV2 );
                glVertex3f( BV1 );
                glVertex3f( TV1 );
                glVertex3f( BV2 );
                glVertex3f( TV0 );
                glVertex3f( BV3 );
                glVertex3f( TV3 );
                glVertex3f( BV0 );
                glVertex3f( TV2 );
            glEnd( );

        glPopMatrix( );

        glutSwapBuffers();

}

/**************************************************************************/
/* A function that handles the keyboard callback
 **************************************************************************/
void keyPressed(unsigned char key, int x, int y)
{
    /* avoid thrashing this procedure */
    usleep(100);

    /* If escape is pressed, kill everything. */
    if (key == ESCAPE) {
        /* shut down our window */
        glutDestroyWindow(window);
        
        /* exit the program...normal termination. */
        exit(0);
    }

    /* Select type of transformation to do */
    if ( key == 'r' ) {
            vector = octrot;
        }
    /* Reset all transformations and go back to WIRE mode */
    if ( key == 'R' ) {
            octrot[X] = 0.0;
            octrot[Y] = 0.0;
            octrot[Z] = 0.0;
        }
    /* Rotation, translation and scale */
    if ( key == 'X' )  vector[X] += DELTA;
    if ( key == 'x' )  vector[X] -= DELTA;
    if ( key == 'Y' )  vector[Y] += DELTA;
    if ( key == 'y' )  vector[Y] -= DELTA;
    if ( key == 'Z' )  vector[Z] += DELTA;
    if ( key == 'z' )  vector[Z] -= DELTA;

    /* Wireframe mode */
    if (key == 'w' ) glPolygonMode( GL_FRONT, GL_LINE );
    if (key == 'W' ) glPolygonMode( GL_FRONT, GL_FILL );

    glutPostRedisplay();
}

