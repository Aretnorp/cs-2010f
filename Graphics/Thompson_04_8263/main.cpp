/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Creates a Puppet model that can be modified via the joints
 *
 *        Version:  1.0
 *        Created:  November 30th, 2010
 *
 *         Author:  Cody Thompson
 *
 *     Difficulty:  The most difficult aspect was the creation of the actual object
 *                  itself which in retrospect I should have not done in such a 
 *                  complex and otherwise complicated manner. Aside from that, minor
 *                  issues with my artistic prowess in terms of developing an eye
 *                  appealing model.
 *     Objectives:  To learn how to create a complex OpenGL application using the
 *                  various things we have learned in this course.
 *           1. To understand hierarchical models
 *           2. To manipulate the matrix stack
 *           3. To work with the zbuffer and back facing polygons
 *           4. To use hidden surface removal
 *           5. To use a display list
 *           6. To use the perspective transformations
 *           7. To create Menus using the glut library
 *           8. To pick and select different objects
 *           9. To manipulate objects using the mouse
 *           10.To add lighting to complex objects
 *           11.To apply material to objects instead of colors
 *           12.To add textures to complex objects
 * =====================================================================================
 */
#include "main.h"

/*-----------------------------------------------------------------------------
*  Variable Definitions
*-----------------------------------------------------------------------------*/
Person* person;
int rotX = 0;
int rotY = 0;
int traX = 0;
int traY = 0;
bool isRightButton = false;

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
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE );

	/* Create an application window of a certain size */
	glutInitWindowSize( 850, 450 );

	/* Create an application window on the screen */
	glutCreateWindow( "Assignment #4: 3D Model" );

	/* Register the function that does drawing */
	glutDisplayFunc( Draw );

	/* Create the Keyboard callback */
	glutKeyboardFunc( Keyboard );
	glutSpecialFunc( SpecialKeyboard );

	/* Create the Reshape callback */
	glutReshapeFunc( Reshape );

	/* Create the Mouse callback */
	glutMouseFunc( Mouse );

	/* Create the Motion callback */
	glutMotionFunc( MouseMove );

	/* Register Exit Handler */
	atexit(ClearMemory);

	/* Enable GL Properties */
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_MULTISAMPLE);

	/* Create a Person */
	person = new Person( );

	/* Create the Menu */
	CreateMiddleMenu( );

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
	delete person;
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

	/* Enable the lighting */
	EnableLighting( );

	/* Rotate the world */
	glPushMatrix( );
		/* Translate */
		glTranslatef(traX, traY, 0);
		glRotatef(rotX, 1.0, 0.0, 0.0);
    	glRotatef(rotY, 0.0, 1.0, 0.0);
    
    	/* Draw the person */
    	person->Draw();
	glPopMatrix( );

	/* Flush the buffer */
	glutSwapBuffers(); 

	return;
}

/*-----------------------------------------------------------------------------
*  Keyboard
*  Handles the keyboard input for each of the various buttons
*-----------------------------------------------------------------------------*/
void Keyboard( unsigned char key, int x, int y )
{
	if(key == 27) /* Escape key */
		exit(0);
	else if(positionMode)
	{
    	/* Determine which key is pressed */
    	switch(key)
    	{
    	case 'a': /* Rotate left */
    		rotY -= 5; break;
    	case 'A':
    		rotY -= 15; break;
    	case 'd': /* Rotate right */
    		rotY += 5; break;
    	case 'D':
    		rotY += 15; break;
    	case 'w': /* Rotate up */
    		rotX += 5; break;
    	case 'W':
    		rotX += 15; break;
    	case 's': /* Rotate down */
    		rotX -= 5; break;
    	case 'S':
    		rotX -= 15; break;
    	default: return; /* Exit if another key was pressed */
    	}
    
    	/* Redraw the Display */
    	glutPostRedisplay();
	}
}

/*-----------------------------------------------------------------------------
*  SpecialKeyboard
*  Handles the special keyboard input for each of the various buttons
*-----------------------------------------------------------------------------*/
void SpecialKeyboard( int key, int x, int y )
{
	if(positionMode)
	{
    	switch(key)
    	{
    	case GLUT_KEY_LEFT:
    		traX -= 10; break;
    	case GLUT_KEY_RIGHT:
    		traX += 10; break;
        case GLUT_KEY_UP:
    		traY += 10; break;
    	case GLUT_KEY_DOWN:
    		traY -= 10; break;
    	default: return; /* Exit if another key was pressed */
    	}
    
    	/* Redraw the Display */
    	glutPostRedisplay();
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
	gluPerspective( 60.0, width / height, 1.0, 1000 );

	/* Change to ModelView Matrix */
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	/* Look at Origin from specified angle */
	gluLookAt(0.0, 0.0, 200.0,
      		0.0, 0.0, 0.0, /* Look at Center */
    		0.0, 1.0, 0.0); /* Look up */
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

	/* Handle the Left Mouse selection */
	if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) &&
	   (jointMode))
	{
		/* Get the Viewport and set to Projection */
		glGetIntegerv( GL_VIEWPORT, viewport );
		glSelectBuffer(BUF_SIZ, nameBuffer);
		glRenderMode(GL_SELECT);

		/* Initialize Object Drawing */
		glInitNames( );
		glPushName( 0 );

		/* Save the Projection matrix */
		glMatrixMode( GL_PROJECTION );
		glPushMatrix( );
		glLoadIdentity( );
		gluPickMatrix( (GLdouble)x, (GLdouble)(viewport[3] - y),
			N, N, viewport );

    	/* Configure Perspective to proper aspect ratio */
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);
    	gluPerspective( 60.0, width / height, 1.0, 1000 );

		/* Enable Picking mode */
		glMatrixMode(GL_MODELVIEW);

		/* Redraw Scene with Picking enabled */
		Draw( );

		/* Reset Projection */
		glMatrixMode( GL_PROJECTION );
		glPopMatrix( );

		/* Get the number of hits */
		hits = glRenderMode( GL_RENDER );
		ProcessHits( hits, nameBuffer );

		/* Call a movement */
		//MouseMove( x, y );

		/* Draw the display */
		glMatrixMode( GL_MODELVIEW );
		glutPostRedisplay( );
	}

	/* Configure the Right Mouse button detection */
	else if((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
		isRightButton = true;
	else if((button == GLUT_RIGHT_BUTTON) && (state == GLUT_UP))
		isRightButton = false;
}

/*-----------------------------------------------------------------------------
*  CreateText
*  Draws a set of text using the GLUT bitmap String for a location at x and
*  y for a set font and buf
*-----------------------------------------------------------------------------*/
void CreateText( float x, float y, void* font, char* buf) 
{
	/* Set the color */
	glColor3f(0.0, 0.7, 0.0);

	/* Set the position */
	glRasterPos2f(x, y);

	/* Print the text */
	glutBitmapString(font, (const unsigned char*)buf);
}

/*-----------------------------------------------------------------------------
 *  ProcessHits
 *  Processes which items have been clicked
 *-----------------------------------------------------------------------------*/
void ProcessHits( GLint hits, GLuint buffer[] ) 
{
    GLuint i, j;
    GLuint names, *ptr;


    ptr = buffer;
    for(i = 0; i < hits; ++i)
    {
        names = *ptr;

        /* Skip over number of names and depths */
        ptr += 3;

        /* Check each name in the records */
        for(j = 0; j < names; ++j)
        {
			if(*ptr != 0)
			{	
    			if (Picking::IsSelectedIndex(*ptr))
    			{
        			Picking::RemoveSelectedIndex(*ptr);
    			}
    			else
    			{
    				Picking::AddSelectedIndex(*ptr);
    			}
			}

            /* Go to the next hit record */
            ptr++;
        }
    }
}

/*-----------------------------------------------------------------------------
 *  MouseMove
 *  Handles when the mouse is moved in the window
 *-----------------------------------------------------------------------------*/
void MouseMove( int x, int y )
{
    GLdouble objX, objY, objZ;
    GLfloat winX, winY;
    GLfloat deltaX, deltaY;
    GLint view[4];
    GLdouble p[MATRIX_SIZE];
    GLdouble m[MATRIX_SIZE];
    GLdouble z;

    /* Get the matrices and the viewport */
    glGetDoublev( GL_PROJECTION_MATRIX, p );
    glGetDoublev( GL_MODELVIEW_MATRIX, m );
    glGetIntegerv( GL_VIEWPORT, view );

    /* Get the window coordinates */
    winX = (float)x;
    winY = (float)view[3] - (float)y;

    /* Unproject the coordinates from the window */
    gluUnProject( winX, winY, 0.5, m, p, view, &objX, &objY, &objZ );

	/* Check for selected items */
	if(!Picking::IsEmpty() && (isRightButton))
	{
		person->RotateObjects((int)(objX * 300), 
							 (int)(objY * 300));
	}

	/* Refresh the screen */
	glutPostRedisplay( );
}

/*-----------------------------------------------------------------------------
 *  Reset
 *  Resets the model to have its default values
 *-----------------------------------------------------------------------------*/
void Reset( void )
{
	/* Delete the Person object */
	delete person;
	person = new Person( );

	/* Default all rotations and translations */
	rotX = rotY = traX = traY = 0;
}

/*-----------------------------------------------------------------------------
 *  EnableLighting
 *  Toggles lighting dependent on the Menu settings
 *-----------------------------------------------------------------------------*/
void EnableLighting( void )
{
	if(lightMode)
	{
		/* Create a Light Position */
		GLfloat lightPos[] = { 50, 50, 50, 1 };

		/* Enable the lighting */
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

		/* Enable the Material colors */
		glColorMaterial(GL_FRONT, GL_DIFFUSE);
		glEnable(GL_NORMALIZE);

		/* Enable the Shading */
		flatShade? glShadeModel(GL_FLAT) :
				   glShadeModel(GL_SMOOTH);
	}
	else
	{
		/* Disable the Lighting */
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_NORMALIZE);
		glDisable(GL_COLOR_MATERIAL);
	}
}

