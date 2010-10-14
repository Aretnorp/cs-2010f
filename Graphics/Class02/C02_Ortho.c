/* PROGRAM:  morph.c 
   AUTHOR:   Carolina Ayala 
   DATE:     01/25/2010 
   PURPOSE:  Simple animation Hands on Learning
   NOTES:    Modification from circle*.c 
*/

/**************************************************************************/
/* Declare include files 
 **************************************************************************/
#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

/**************************************************************************/
/* Defines
 ***************************************************************************/
#define TITLE "-:: Star Morphin ::-"
#define ON 	1
#define OFF	0
#define MAX_POINTS 20
#define MIN_POINTS 5
#define SLATE     0.32, 0.32, 0.32
#define STEELBLUE 0.65, 0.72, 0.82
#define COBALT    0.24, 0.36, 0.68

/**************************************************************************/
/* Declare function prototypes
 ***************************************************************************/
void Star( float, float, int, float, float );  /* Draws a Star */
void Draw( void );
void Morph( int );
void Init( void );
void Reshape(int Width, int Height); 
void keyPressed(unsigned char key, int x, int y);

/**************************************************************************/
/* Global Var 
 ***************************************************************************/
static int frames = 4;

/* Star Global Variable */
float R1 = 4;
float R2 = 2;
int   P = MIN_POINTS;
int   GROW = ON;

/**************************************************************************/
/* main: all initialization and callback registration.
 ***************************************************************************/
int main( int argc, char *argv[] ) {

  	glutInit( &argc, argv );

	if ( argc == 2 ) 
		frames = atoi( argv[1] );

  	glutInitDisplayMode( GLUT_DOUBLE );
  	glutCreateWindow( TITLE );
  	glutDisplayFunc( Draw );
  	glutReshapeFunc( Reshape );

        glutTimerFunc( 100, Morph, 1 );
	Init( );
   	glutMainLoop();

   return( 0 );  /* NOTE: this is here only for ANSI requirements */
}

/**************************************************************************/
/* Init done here - functions that need to be called only once
 **************************************************************************/
void Init( void ) {
	
	glClearColor( SLATE, 1.0 );
	glEnable( GL_CULL_FACE );

}
/**************************************************************************/
/* Morph -- Your morphing function  
 * Function you need to complete.
 * You can create a morphing as changing number of Points or
 * changing the values for R1 / R2
 * You can even think about "exploding" the star
 **************************************************************************/
void Morph( int s ) {
        R1 += s;
        R2 += s;

	glutPostRedisplay();

        if(R1 < 10)
            glutTimerFunc( 100, Morph, 1 );
        else
            glutTimerFunc( 100, Morph, -1);


}
/**************************************************************************/
/* A function which draws  
 **************************************************************************/
void Draw( void ) {

	int cx = 0.0, 
  	    cy =0.0;

  	/* Clear the screen ... */
   	glClear( GL_COLOR_BUFFER_BIT );

	
  	/*------------------------------------------------------
         * Draw the star as a fill polygon 
         *-----------------------------------------------------*/
	glPolygonMode ( GL_FRONT, GL_FILL );
	glColor3f( STEELBLUE );   
   	Star( R1, R2, P, cx, cy );

  	/*------------------------------------------------------
         * Draw the star as a line polygon 
         *-----------------------------------------------------*/
	glPolygonMode ( GL_FRONT, GL_LINE );
	glColor3f( COBALT );   
   	Star( R1, R2, P, cx, cy );

   	glutSwapBuffers();

   	return;
}
/**************************************************************************/
/* A function which draws a Star with p points  
 **************************************************************************/
void Star( float r1, float r2, int p, float a, float b ) {

	float angle, r;
   	int i;

   	glBegin( GL_TRIANGLE_FAN );
   		glVertex3f( a, b, 0.0 );
   		for (i = 0,  angle = 0.0; i <= 2*p ; i++,angle += M_PI/p) {
			r = ( i % 2 ? r1 : r2 );
         		glVertex3f( r*cos(angle) + a, r*sin(angle) + b, 0.0 );
   		}		
   	glEnd( ); 

   	return;
}
/**************************************************************************/
/* A reshape function which handles the resize of the window
 *  **************************************************************************/
void Reshape(int Width, int Height) {

	glViewport( 0, 0, Width, Height );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( -10.0, 10.0,  -10.0, 10.0,  -10.0, 10.0 );
	glMatrixMode(GL_MODELVIEW);
}

