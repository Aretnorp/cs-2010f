/*
 * =====================================================================================
 *
 *       Filename:  Thompson_01_8263.c
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
#include <string.h>
#include "list.h"

#define TRUE 1
#define FALSE 0

#define NUM_LISTS 2

#define N 1

#define BUF_SIZ 256

#define DEFAULT_FONT GLUT_BITMAP_8_BY_13

#define VERTICAL 1
#define HORIZONTAL 0

#define AVAILABLE 100
#define SELECTED 200

#define HOUSE 2

/*-----------------------------------------------------------------------------
 *  Function Definitions
 *-----------------------------------------------------------------------------*/
void Draw( void );
void Keyboard( unsigned char , int , int );
void Reshape( int, int );
void ClearMemory( void );
void DrawText( float, float, void*, char* );
void InitShapes( void );
void ProcessHits( GLint, GLuint[] );
void DrawShapes( GLenum );
void Mouse( int, int, int, int );
void MouseMove( int, int );

void RunTransform( Transform* );
void ReadTransforms( char*, TransformList* );
void RunTransformList( TransformList* );
void CopyList( TransformList*, TransformList* );
void CreateTransforms( TransformList*, int, int );


/*-----------------------------------------------------------------------------
 *  Global Definitions
 *-----------------------------------------------------------------------------*/
int xmin = -100;
int xmax = 130;
int ymin = -130;
int ymax = 100;
TransformList tlLevel;
TransformList tlSelectedTransforms;
TransformList tlAvailableTransforms;
GLdouble lastX = 0;
GLdouble lastY = 0;
int selectedIndex = 0;
TransformNode* selectedNode;

/*-----------------------------------------------------------------------------
 *  Main Function
 *  Initiates the graphics buffer, creates the window
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
    glutCreateWindow( "Assignment #n: An Assignment" );

    /* Register the function that does drawing */
    glutDisplayFunc( Draw );

    /* Create the Keyboard callback */
    glutKeyboardFunc( Keyboard );

    /* Create the Mouse callbacks */
    glutMouseFunc( Mouse ); 
    glutMotionFunc( MouseMove );

    /* Create the Reshape callback */
    glutReshapeFunc( Reshape );

    /* Enable GL Properties */
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    /* Register Exit Handler */
    atexit(ClearMemory);

    /* Initialize the House Shapes */
    InitShapes( );

    /* Add the transform */
    tlLevel.root = NULL;
    tlSelectedTransforms.root = NULL;
    tlAvailableTransforms.root = NULL;
    ReadTransforms("tx 50,sx 2,rz 180", &tlLevel);
    PrintList(&tlLevel);
    CopyList( &tlLevel, &tlAvailableTransforms );

    /* Turn over control to OpenGL */
    glutMainLoop();

    return( 0 );  /* NOTE: this is here only for ANSI requirements */
}

/*-----------------------------------------------------------------------------
 *  InitShapes
 *  Create the shapes used in the project
 *-----------------------------------------------------------------------------*/
void InitShapes( void )
{
    /* Define the two new lists */
    glNewList( 'h', GL_COMPILE );
        /* Draw the main part of the house */
        glColor3f( 1.0, 0.0, 0.0 );
        glBegin( GL_QUADS );
            glVertex3f(  10.0,  10.0, 0.0 );
            glVertex3f( -10.0,  10.0, 0.0 );
            glVertex3f( -10.0, -10.0, 0.0 );
            glVertex3f(  10.0, -10.0, 0.0 );
        glEnd( );

        /* Draw the top of the house */
        glColor3f( 0.0, 1.0, 0.0 );
        glBegin( GL_TRIANGLES );
            glVertex3f(  12.5,  10.0, 0.0 );
            glVertex3f(   0.0,  20.0, 0.0 );
            glVertex3f( -12.5,  10.0, 0.0 );
        glEnd( );
        glColor3f( 1.0, 1.0, 1.0 );
    glEndList( );

    /* Define the two new lists */
    glNewList( 'l', GL_COMPILE );
        /* Draw the main part of the house */
        glColor3f( 0.5, 0.0, 0.0 );
        glBegin( GL_QUADS );
            glVertex3f(  10.0,  10.0, 0.0 );
            glVertex3f( -10.0,  10.0, 0.0 );
            glVertex3f( -10.0, -10.0, 0.0 );
            glVertex3f(  10.0, -10.0, 0.0 );
        glEnd( );

        /* Draw the top of the house */
        glColor3f( 0.0, 0.5, 0.0 );
        glBegin( GL_TRIANGLES );
            glVertex3f(  12.5,  10.0, 0.0 );
            glVertex3f(   0.0,  20.0, 0.0 );
            glVertex3f( -12.5,  10.0, 0.0 );
        glEnd( );
        glColor3f( 1.0, 1.0, 1.0 );
    glEndList( );

    /* Define the list for the Shape */
    glNewList( 't', GL_COMPILE );
        glColor3f( 0.5, 0.0, 1.0 );
        glBegin( GL_POLYGON );
            glVertex3f(  10.0,  0.0,  0.0 );
            glVertex3f(   5.0,  7.5,  0.0 );
            glVertex3f( -10.0,  7.5,  0.0 );
            glVertex3f(  -5.0,  0.0,  0.0 );
            glVertex3f( -10.0, -7.5,  0.0 );
            glVertex3f(   5.0, -7.5,  0.0 );
        glEnd( );
        glColor3f( 1.0, 1.0, 1.0 );
    glEndList( );
}

/*-----------------------------------------------------------------------------
 *  ClearMemory
 *  Clears the dynamically allocated memory at close
 *-----------------------------------------------------------------------------*/
void ClearMemory( void )
{
    //Clear our lists
}

/*-----------------------------------------------------------------------------
 *  Draw
 *  The Draw function is the main loop for the Graphics process. Draws each
 *  viewport and the lines within them
 *-----------------------------------------------------------------------------*/
void Draw( void )
{
    char buf[BUF_SIZ];

    /* Clear the screen ... */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* Draw the first set of Available Transforms */
    glPushMatrix( );
        /* Move to origin of first list */
        glTranslatef( 115.0, 90.0, 0.0 );

        /* List drawing */
        CreateTransforms( &tlAvailableTransforms, VERTICAL, AVAILABLE );
    glPopMatrix( );

    /* Draw the second set of Used Transforms */
    glPushMatrix( );
        /* Move to origin of first list */
        glTranslatef( 115.0, -120.0, 0.0 );

        /* List drawing */
        CreateTransforms( &tlSelectedTransforms, HORIZONTAL, SELECTED );
    glPopMatrix( );

    glPushMatrix( );
        /* Do all level transforms */
        RunTransformList( &tlLevel );

        /* Create model house */
        glLoadName( 1 );
        glCallList( 'l' );
    glPopMatrix( );

    /* Create the new house */
    glPushMatrix(  );
        /* Do all user seelcted transforms */
        RunTransformList( &tlSelectedTransforms );

        glLoadName( HOUSE );
        glCallList( 'h' );
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
    /* Determine which key is pressed */
    switch(key)
    {
        case 27: /* Escape the Program */
            exit(0);
            break;
        default: return; /* Exit if another key was pressed */
    }

    /* Redraw the Display */
    glutPostRedisplay();
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

    if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
    {
        /* Get the Viewport and set to Projection */
        glGetIntegerv( GL_VIEWPORT, viewport );
        glMatrixMode( GL_PROJECTION );

        /* Save the Projection matrix */
        glPushMatrix( );
        glLoadIdentity( );
        gluPickMatrix( (GLdouble)x, (GLdouble)(viewport[3] - y),
                N, N, viewport );
        gluOrtho2D( xmin, xmax, ymin, ymax );

        /* Set the Render Mode to the Selection mode */
        glMatrixMode( GL_MODELVIEW );
        glSelectBuffer(BUF_SIZ, nameBuffer);
        glRenderMode( GL_SELECT );

        /* Initialize the Object Naming */
        glInitNames( );
        glPushName( 0 );

        /* Draw the Shapes with Select enabled */
        Draw( );

        /* Reset the Projection Matrix */
        glMatrixMode( GL_PROJECTION );
        glPopMatrix( );

        /* Return drawing to MODELVIEW */
        glMatrixMode( GL_MODELVIEW );

        /* Get the number of hits */
        hits = glRenderMode( GL_RENDER );
        ProcessHits( hits, nameBuffer );

        /* Call a movement */
        MouseMove( x, y );

        /* Draw the display */
        glutPostRedisplay( );
    }
    else if((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
    {
        if(selectedNode != NULL)
        {
            TransformList* from;
            TransformList* to;

            /* Check if its in the dimension */
            if((selectedIndex / SELECTED) == 1)
            {
                from = &tlSelectedTransforms;
                to = &tlAvailableTransforms;
            }
            else
            {
                from = &tlAvailableTransforms;
                to = &tlSelectedTransforms;
            }

            /* Swap the nodes */
            RemoveNode(from, selectedNode);
            AppendNode(to, selectedNode);

            /* Reset the mouse display */
            selectedIndex = 0;
            selectedNode = NULL;

            /* Set the new position */
            glutPostRedisplay( );
        }
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
    glLoadIdentity( );

    /* Configure Viewport */
    glViewport(0, 0, width, height);

    /* Configure Perspective to proper aspect ratio */
    gluOrtho2D( xmin, xmax, ymin, ymax );

    /* Change to ModelView Matrix */
    glMatrixMode( GL_MODELVIEW );
}

/*-----------------------------------------------------------------------------
 *  DrawText
 *  Draws a set of text using the GLUT bitmap String for a location at x and
 *  y for a set font and buf
 *-----------------------------------------------------------------------------*/
void DrawText( float x, float y, void* font, char* buf) 
{
    /* Set the position */
    glRasterPos3f(x, y, 0.1);

    /* Print the text */
    glutBitmapString(font, buf);
}

/*-----------------------------------------------------------------------------
 *  ProcessHits
 *  Processes which items have been clicked
 *-----------------------------------------------------------------------------*/
void ProcessHits( GLint hits, GLuint buffer[] ) 
{
    unsigned int i, j;
    GLuint names, *ptr;

    printf("hits = %d\n", hits);
    printf("names: %d %d %d %d\n", buffer[0], buffer[1], buffer[2], buffer[3]);

    ptr = buffer;
    for(i = 0; i < hits; ++i)
    {
        names = *ptr;

        /* Skip over number of names and depths */
        ptr += 3;

        /* Check each name in the records */
        for(j = 0; j < names; ++j)
        {
            if(*ptr == 1) printf("Red Rectangle\n");
            else printf("Blue Rectangle\n");

            selectedIndex = *ptr;

            /* Go to the next hit record */
            ptr++;
        }
    }
}

/*-----------------------------------------------------------------------------
 *  RunTransform
 *  Process the transformation given and apply it to the pipeline
 *-----------------------------------------------------------------------------*/
void RunTransform(struct Transform *t)
{
    /* Calculate each dimension */
    GLfloat x = 0;
    GLfloat y = 0;
    if(t->axis == 'x') 
        x = (GLfloat)t->value;
    else
        y = (GLfloat)t->value;

    /* Execute transform */
    switch(t->type)
    {
        case 't': /* Translate */
            glTranslatef(x, y, 0); break;
        case 's': /* Scale */
            if(x < 1) x = 1;
            if(y < 1) y = 1;
            glScalef(x, y, 1); break;
        case 'r': /* Rotate */
            glRotatef(t->value, 0.0, 0.0, 1.0); break;
    }
}

/*-----------------------------------------------------------------------------
 *  RunTransform
 *  Process the transformation given and apply it to the pipeline
 *-----------------------------------------------------------------------------*/
void ReadTransforms(char* buf, TransformList *list)
{
    char type = ' ';
    char axis = ' ';
    int value = 0;
    char* p = buf;

    /* Read the buffer */
    while(p != NULL)
    {
        /* Read the contents of the buffer */
        sscanf(p, "%c%c %d", &type, &axis, &value);

        /* Define a new Transform */
        Transform* t;
        if((t = malloc(sizeof(Transform))) == NULL)
        {
            perror("2D"); exit(EXIT_FAILURE);
        }
        t->type = type;
        t->axis = axis;
        t->value = value;

        /* Add it to the list */
        AddNode(list, t);

        /* Scan for the next item */
        p = strstr(p, ",");
        if(p != NULL)
            p += 1;
    }
}


/*-----------------------------------------------------------------------------
 *  RunTransform
 *  Process the transformation given and apply it to the pipeline
 *-----------------------------------------------------------------------------*/
void RunTransformList(TransformList *list)
{
    TransformNode* node = list->root;

    /* Verify the list */
    if(list->root == NULL)
        return;


    /* Iterate through the list */
    do
    {
        RunTransform(node->data);
        node = node->next;
    } while((node != list->root) && (node != NULL));
}


/*-----------------------------------------------------------------------------
 *  RunTransform
 *  Process the transformation given and apply it to the pipeline
 *-----------------------------------------------------------------------------*/
void CreateTransforms(TransformList *list, int dimension, int start)
{
    TransformNode* node = list->root;
    char buf[BUF_SIZ];
    int i;

    /* Verify the list */
    if(list->root == NULL)
        return;

    /* Iterate through the list */
    i = start;
    do
    {
        /* Draw the shape */
        glLoadName(i);
        glPushMatrix( );
            if(selectedIndex == i)
            {
                glLoadIdentity( );
                glTranslatef( lastX, lastY, 0.0 );
                selectedNode = node;
            }
            glCallList('t');

            /* Write the text */
            sprintf(buf, "%c%c=%d", toupper(node->data->type),
                    node->data->axis, node->data->value);
            DrawText(-5, -2, DEFAULT_FONT, buf);
        glPopMatrix( );

        /* Transform the next list down */
        if(dimension == VERTICAL)
            glTranslatef( 0.0, -20.0, 0.0 );
        /* Transform the next list left */
        else
            glTranslatef(-20.0, 0.0, 0.0 );

        node = node->next;
        ++i;
    } while((node != list->root) && (node != NULL));
}

void MouseMove( int x, int y )
{
    GLdouble objX, objY, objZ;
    GLfloat winX, winY;
    GLfloat deltaX, deltaY;
    GLint view[4];
    GLdouble p[16];
    GLdouble m[16];
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

    /* Store the coordinates */
    if(selectedIndex != 0)
    {
        /* Calculate the Delta */
        if((selectedIndex == HOUSE) && (tlSelectedTransforms.root != NULL))
        {
            Transform* t = tlSelectedTransforms.root->prev->data;
            deltaX = objX - lastX;
            deltaY = objY - lastY;

            /* Ensure there is a list */
            if(t->type == 'r')
                t->value = objX * 2;
            else if(t->axis == 'x')
                t->value = objX / 2;
            else
                t->value = objY;
        }

        /* Store the last values */
        lastX = objX;
        lastY = objY;
        glutPostRedisplay( );
    }
}
