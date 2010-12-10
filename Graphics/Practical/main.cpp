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
 * =====================================================================================
 */
#include "main.h"

/*-----------------------------------------------------------------------------
*  Variable Definitions
*-----------------------------------------------------------------------------*/
int index;

#define P1 0.000000, 0.000000,  2.000000
#define P2 1.902113, 0.000000,  0.618034
#define P3 1.175570, 0.000000, -1.618034

#define P4 -1.175571, 0.000000, -1.618034
#define P5 -1.902113, 0.000000,  0.618034

#define TOP 0.0, 1.0, 0.0
#define BOTTOM 0.0, -1.0, 0.0

GLfloat lightPos[] = { 2.5, 2.5, 2.5, 1 };

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

    /* Create the Reshape callback */
    glutReshapeFunc( Reshape );

    /* Register Exit Handler */
    atexit(ClearMemory);

    /* Enable GL Properties */
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    /* Create the Menu */
    CreateMiddleMenu( );

    /* Create the Shape */
    CreatePrimitive( );

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
    /* Clear the screen ... */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* Enable the lighting */
    EnableLighting( );

    /* Set the correct render mode */
    if((positionalLight) || (globalLight))
        glPolygonMode(GL_FRONT, GL_FILL);
    else
        glPolygonMode(GL_FRONT, GL_LINE);

    glPushMatrix( );
        /* Draw the world coordinate system */
        glColor3f(0.0, 0.0, 1.0);
        glCallList(index + 1);
        
        /* Draw the Light point */
        glColor3f(1.0, 1.0, 0.0);
        glPointSize(5);
        glBegin(GL_POINTS);
            glVertex4fv(lightPos);
        glEnd( );
    glPopMatrix( );

    /* Rotate the world */
    glPushMatrix( );
        /* Use the user transformations */
        transforms.GetTranslate( );
        transforms.GetRotation( );

        /* Draw the Coordinate system */
        glColor3f(1.0, 0.0, 0.0);
        glCallList(index + 1);

        /* Scale the system */
        transforms.GetScale( );

        /* Draw the Shape */
        glColor3f(1.0, 1.0, 1.0);
        glCallList(index);
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
    if((key == 27) || (key == 'Q')) /* Escape key */
            exit(0);
    else if(positionMode)
    {
        /* Determine which key is pressed */
        switch(key)
        {
        /* Assignment Specification Keys */
        case 'R':
                Reset( ); break;
        case 'x':
                if(!lightMode)
                    transforms.SetX(-15);
                else
                    lightPos[0] -= 0.5;
                break;
        case 'X':
                if(!lightMode)
                    transforms.SetX(+15);
                else
                    lightPos[0] += 0.5;
                break;
        case 'y':
                if(!lightMode)
                    transforms.SetY(-15);
                else
                    lightPos[1] -= 0.5;
                break;
        case 'Y':
                if(!lightMode)
                    transforms.SetY(+15);
                else
                    lightPos[1] += 0.5;
                break;
        case 'z':
                if(!lightMode)
                    transforms.SetZ(-15);
                else
                    lightPos[2] -= 0.5;
                break;
        case 'Z':
                if(!lightMode)
                    transforms.SetZ(+15);
                else
                    lightPos[2] += 0.5;
                break;
        case 'l':
        case 'L':
                Menu(MENU_GLOBAL); break;
        case 'p':
        case 'P':
                Menu(MENU_POSITIONAL); break;
        case 'm':
        case 'M':
                lightMode = !lightMode; break;
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
    gluLookAt(0.0, 0.0, 10.0,
              0.0, 0.0, 0.0, /* Look at Center */
              0.0, 1.0, 0.0); /* Look up */
}

/*-----------------------------------------------------------------------------
 *  Reset
 *  Resets the model to have its default values
 *-----------------------------------------------------------------------------*/
void Reset( void )
{
    /* Default all rotations and translations */
    transforms.Reset();

    /* Set the light position */
    lightPos[0] = lightPos[1] = lightPos[2] = 2.5;
}

/*-----------------------------------------------------------------------------
 *  EnableLighting
 *  Toggles lighting dependent on the Menu settings
 *-----------------------------------------------------------------------------*/
void EnableLighting( void )
{
    /* Enable the lighting */
    if(globalLight) glEnable(GL_LIGHTING);
    else glDisable(GL_LIGHTING);

    if(positionalLight) glEnable(GL_LIGHT0);
    else glDisable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    /* Enable the Material colors */
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_NORMALIZE);

    /* Enable the Shading */
    glShadeModel(GL_SMOOTH);
}

/*-----------------------------------------------------------------------------
 *  CreatePrimitive
 *  Instantiate the primitives
 *-----------------------------------------------------------------------------*/
void CreatePrimitive( void )
{
    /* Create the list */
    index = glGenLists(2);

    /* Define the list */
    glNewList(index, GL_COMPILE);
        GLfloat value[] = { 0.0, 1.0, 0.0, 1.0 };
        glMaterialfv(GL_FRONT, GL_SPECULAR, value);
        glMaterialfv(GL_FRONT, GL_AMBIENT, value);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, value);
        glMaterialf (GL_FRONT, GL_SHININESS, 15 );

        /* Draw the Top Pyramid */
        glBegin(GL_TRIANGLE_FAN);
            GetSmoothNormals(TOP);
            glVertex3f(TOP);
            GetSmoothNormals(P1);
            glVertex3f(P1);
            GetSmoothNormals(P2);
            glVertex3f(P2);

            GetSmoothNormals(P3);
            glVertex3f(P3);
            GetSmoothNormals(P4);
            glVertex3f(P4);
            GetSmoothNormals(P5);
            glVertex3f(P5);
            GetSmoothNormals(P1);
            glVertex3f(P1);
        glEnd( );

        /* Draw the Bottom Pyramid */
        glBegin(GL_TRIANGLE_FAN);
            GetSmoothNormals(BOTTOM);
            glVertex3f(BOTTOM);
            GetSmoothNormals(P1);
            glVertex3f(P1);
            GetSmoothNormals(P5);
            glVertex3f(P5);

            GetSmoothNormals(P4);
            glVertex3f(P4);
            GetSmoothNormals(P3);
            glVertex3f(P3);
            GetSmoothNormals(P2);
            glVertex3f(P2);
            GetSmoothNormals(P1);
            glVertex3f(P1);
        glEnd( );
    glEndList( );

    /* Create a Coordinate System */
    glNewList(index + 1, GL_COMPILE);
        glBegin(GL_LINES);
            /* X axis */
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);

            /* Y axis */
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, 1.0, 0.0);

            /* Z axis */
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, 0.0, 1.0);
        glEnd( );
    glEndList( );
}
