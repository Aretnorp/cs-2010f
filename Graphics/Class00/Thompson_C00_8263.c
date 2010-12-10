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
#include <math.h>

/**************************************************************************/
/* Declare function prototypes
 **************************************************************************/
void Draw( void );
void DrawLine( float , float , float, float );  /* Draws a line */

/**************************************************************************/
/* main: all initialization and callback registration.
 **************************************************************************/
int main( int argc, char *argv[] )
{
	/* Initialize the drawing environment */
	glutInit( &argc, argv );

	/* Create an application window on the screen */
	glutCreateWindow( "My first OpenGL program" );

	/* Register the function that does drawing */
	glutDisplayFunc( Draw );
  
	/* Turn over control to OpenGL */
	glutMainLoop();

	return( 0 );  /* NOTE: this is here only for ANSI requirements */
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

/**************************************************************************/
/* A function which draws a line 
 **************************************************************************/
void DrawTriangle( float x0, float y0, 
               float x1, float y1,
		float x2, float y2)
{
  	/* Draw a line  */
	glBegin( GL_LINE_LOOP );
    	 	glVertex2f( x0, y0 );
	  	glVertex2f( x1, y1 );
	  	glVertex2f( x2, y2 );
  	glEnd();

  	return;
}

/**************************************************************************/
/* A function which draws a line 
 **************************************************************************/
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

/**************************************************************************/
/* A function which draws  
 **************************************************************************/
void Draw( void )
{
  	 /* Clear the screen ... */
   	glClear( GL_COLOR_BUFFER_BIT );

   	/* Draw the line */
/*   	DrawLine( -0.8, -0.8, 0.8, 0.8 );
	DrawLine( -0.8, 0, 0.8, 0 );
	DrawLine( -0.8, 0, -0.8, -0.8 );
	DrawLine( 0.8, 0, 0.8, 0.8 );
*/

	/* Draw the Triangle */
	/* DrawTriangle(-0.8, -0.8, 0.0, 0.8, 0.8, -0.8); */

	/* Set the Color */
	glColor3f(1.0, 0.0, 0.0);

	/* Draw the Polygon */
	DrawPolygon(0.5, 10);

	/* Draw the Triangles */
	/*for(int i = 0; i < 100; ++i)
	{
		DrawTriangle(0.0, 0.0,
			     
	}*/
	
  	/* Flush the buffer */
  	glFlush(); 
   
   	return;
}
