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
int rotX = 0;
int rotY = 0;
float traX = 0;
float traY = 0;
bool isRightButton = false;
int index;



#define P1 0.000000, 0.000000,  2.000000
#define P2 1.902113, 0.000000,  0.618034
#define P3 1.175570, 0.000000, -1.618034

#define P4 -1.175571, 0.000000, -1.618034
#define P5 -1.902113, 0.000000,  0.618034

#define TOP 0.0, 1.0, 0.0
#define BOTTOM 0.0, -1.0, 0.0

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


        /* Assignment Specification Keys */
        case 'R':
                Reset( ); break;
        case 'x':
                transforms.SetX(-15); break;
        case 'X':
                transforms.SetX(+15); break;
        case 'y':
                transforms.SetY(-15); break;
        case 'Y':
                transforms.SetY(+15); break;
        case 'z':
                transforms.SetZ(-15); break;
        case 'Z':
                transforms.SetZ(+15); break;
        case 'l':
        case 'L':
                Menu(MENU_GLOBAL); break;
        case 'p':
        case 'P':
                Menu(MENU_POSITIONAL); break;
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
            traX -= 0.1; break;
    case GLUT_KEY_RIGHT:
            traX += 0.1; break;
    case GLUT_KEY_UP:
            traY += 0.1; break;
    case GLUT_KEY_DOWN:
            traY -= 0.1; break;
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
*  Mouse
*  Handles Mouse Movement and Selection
*-----------------------------------------------------------------------------*/
void Mouse(int button, int state, int x, int y)
{
    GLuint nameBuffer[BUF_SIZ];
    GLint hits;
    GLint viewport[4];

    /* Handle the Left Mouse selection */
    if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
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
                /* Do some selection */
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
//    if(!Picking::IsEmpty() && (isRightButton))
//    {
//        person->RotateObjects((int)(objX * 300),
//                                (int)(objY * 300));
//    }

    /* Refresh the screen */
    glutPostRedisplay( );
}

/*-----------------------------------------------------------------------------
 *  Reset
 *  Resets the model to have its default values
 *-----------------------------------------------------------------------------*/
void Reset( void )
{
    /* Default all rotations and translations */
    rotX = rotY = traX = traY = 0;

    /* Default all rotations and translations */
    transforms.Reset();
}

/*-----------------------------------------------------------------------------
 *  EnableLighting
 *  Toggles lighting dependent on the Menu settings
 *-----------------------------------------------------------------------------*/
void EnableLighting( void )
{
    /* Create a Light Position */
    GLfloat lightPos[] = { 10, 10, 10, 1 };

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
