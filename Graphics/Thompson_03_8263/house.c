/*
 * =====================================================================================
 *
 *       Filename:  House.c
 *
 *    Description:  Provides an interface to a 2D transformation game. Levels are read
 *                  from a file. Each level is a list of transformations. The users
 *                  objective is to figure out the value of each of the transformations.
 *
 *        Version:  1.0
 *        Created:  11/11/2010 4:00:00 PM
 *
 *         Author:  Cody Thompson
 *
 *     Difficulty:  The most difficult aspects were the drag and drop functionality,
 *                  and implementing a functional linked list within the assignment
 *                  specification. Once the custom tailored Linked List was complete
 *                  and the drag drop code properly implemented, the remaining
 *                  sections fell into place. I would rate the level of difficulty at
 *                  a 4, making it among the most difficult of Graphics assignments
 *                  yet.
 *     Objectives:  Receive a better grasp of Transformations within a 2D Space. Make
 *                  use of Drag and Drop Mouse related functions in GLUT. Learn pop
 *                  and push matrices. Implement a custom set of transformations within
 *                  an assignment.
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

#define MATRIX_SIZE 16
#define EPSILON 0.000001

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
void ReadLevel( FILE*, char* );

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
TransformList* selectedList;
int levelComplete = FALSE;
int gameComplete = FALSE;

char currentLevelString[BUF_SIZ];
FILE* file;

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
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_MULTISAMPLE );

    /* Create an application window of a certain size */
    glutInitWindowSize( 850, 450 );

    /* Create an application window on the screen */
    glutCreateWindow( "Assignment #3: 2D Transformations" );

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
    glEnable(GL_MULTISAMPLE);

    /* Register Exit Handler */
    atexit(ClearMemory);

    /* Initialize the House Shapes */
    InitShapes( );

    /* Add the transform */
    tlLevel.root = NULL;
    tlSelectedTransforms.root = NULL;
    tlAvailableTransforms.root = NULL;

    /* Open the file */
    file = fopen("level.dat", "r");
    ReadLevel(file, currentLevelString);

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
        glBegin( GL_POLYGON );
            glVertex3f(  10.0,  0.0,  0.0 );
            glVertex3f(   5.0,  7.5,  0.0 );
            glVertex3f( -10.0,  7.5,  0.0 );
            glVertex3f(  -5.0,  0.0,  0.0 );
            glVertex3f( -10.0, -7.5,  0.0 );
            glVertex3f(   5.0, -7.5,  0.0 );
        glEnd( );
    glEndList( );

    /* Define the available list for the Shape */
    glNewList( 'a', GL_COMPILE );
        glColor3f( 0.0, 0.0, 0.5 );
        glBegin( GL_QUADS );
            glVertex3f(  130.0, 100.0,  0.5 );
            glVertex3f(  100.0, 100.0,  0.5 );
            glVertex3f(  100.0,-130.0,  0.5 );
            glVertex3f(  130.0,-130.0,  0.5 );
        glEnd( );
        glColor3f( 1.0, 1.0, 1.0 );
    glEndList( );

    /* Define the selected list for the Shape */
    glNewList( 's', GL_COMPILE );
        glColor3f( 0.5, 0.0, 0.0 );
        glBegin( GL_QUADS );
            glVertex3f(  100.0,-100.0, -0.5 );
            glVertex3f( -100.0,-100.0,  0.5 );
            glVertex3f( -100.0,-130.0,  0.5 );
            glVertex3f(  100.0,-130.0,  0.5 );
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
    /* Clear each list */
    ClearList( &tlAvailableTransforms );
    ClearList( &tlSelectedTransforms );
    ClearList( &tlLevel );

    /* Close the file */
    fclose(file);
}

/*-----------------------------------------------------------------------------
 *  Draw
 *  The Draw function is the main loop for the Graphics process. Draws each
 *  viewport and the lines within them
 *-----------------------------------------------------------------------------*/
void Draw( void )
{
    char buf[BUF_SIZ];
    GLdouble answer[MATRIX_SIZE];
    GLdouble attempt[MATRIX_SIZE];

    /* Clear the screen ... */
    glClear( GL_COLOR_BUFFER_BIT );

    if(gameComplete)
    {
        DrawText(-25.0, -25.0, DEFAULT_FONT, "GAME OVER! YOU WIN!");
    }
    else if(levelComplete)
    {
        DrawText(-25.0, -25.0, DEFAULT_FONT, "LEVEL COMPLETE!");
    }
    else
    {
        glPushMatrix( );
            /* Draw the Outlines for Transforms */
            glCallList('a');
            glCallList('s');

            /* Draw the Axes */
            glBegin( GL_LINES );
                glColor3f( 0.5, 0.5, 0.5 );
                glVertex3f( 100.0, 0.0, 0.0 );
                glVertex3f(-100.0, 0.0, 0.0 );
                glVertex3f( 0.0, 100.0, 0.0 );
                glVertex3f( 0.0,-100.0, 0.0 );
                glColor3f( 1.0, 1.0, 1.0 );
            glEnd( );
        glPopMatrix( );

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
            glTranslatef( -85.0, -120.0, 0.0 );

            /* List drawing */
            CreateTransforms( &tlSelectedTransforms, HORIZONTAL, SELECTED );
        glPopMatrix( );

        glPushMatrix( );
            /* Do all level transforms */
            RunTransformList( &tlLevel );

            /* Create model house */
            glLoadName( 1 );
            glCallList( 'l' );

            /* Get the modelview matrix */
            glGetDoublev( GL_MODELVIEW_MATRIX, answer );
        glPopMatrix( );

        /* Create the new house */
        glPushMatrix(  );
            /* Do all user selected transforms */
            RunTransformList( &tlSelectedTransforms );

            /* Create attempt house */
            glLoadName( HOUSE );
            glCallList( 'h' );

            /* Get the modelview matrix */
            glGetDoublev( GL_MODELVIEW_MATRIX, attempt );
        glPopMatrix( );

        /* Compare the model */
        if(CompareMatrices(answer, attempt))
        {
            levelComplete = TRUE;
            glutPostRedisplay( );
        }
    }

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
        default: 
            if(gameComplete)
            {
                exit(EXIT_SUCCESS);
            }
            else if(levelComplete)
            {
                /* Clear the Lists */
                ClearList(&tlLevel);
                ClearList(&tlSelectedTransforms);
                ClearList(&tlAvailableTransforms);

                /* Load the next level */
                ReadLevel(file, currentLevelString);

                /* Reset the pointers */
                selectedIndex = 0;
                selectedNode = NULL;

                /* Clear the level */
                levelComplete = FALSE;
            }
            else /* Exit if another key was pressed */
                return;
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

    if(levelComplete == TRUE)
        return;

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
            TransformList* from = NULL;
            TransformList* to = NULL;

            /* Check if its in the dimension */
            if(((selectedIndex / SELECTED) == 1) && (lastX > 100.0) && (lastY > -100))
            {
                from = &tlSelectedTransforms;
                to = &tlAvailableTransforms;
                selectedList = &tlAvailableTransforms;
            }
            else if(((selectedIndex / AVAILABLE) == 1) && (lastY < -100) && (lastX < 100.0))
            {
                from = &tlAvailableTransforms;
                to = &tlSelectedTransforms;
                selectedList = &tlSelectedTransforms;
            }

            if((from != NULL) && (to != NULL))
            {
                /* Swap the nodes */
                RemoveNode(from, selectedNode);
                AppendNode(to, selectedNode);
            }

            /* Reset the mouse display */
            selectedIndex = 0;

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

    ptr = buffer;
    for(i = 0; i < hits; ++i)
    {
        names = *ptr;

        /* Skip over number of names and depths */
        ptr += 3;

        /* Check each name in the records */
        for(j = 0; j < names; ++j)
        {
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
            if(x == 0) x = 1;
            if(y == 0) y = 1;
            glScalef(x, y, 1); break;
        case 'r': /* Rotate */
            glRotatef(t->value, 0.0, 0.0, 1.0); break;
    }
}

/*-----------------------------------------------------------------------------
 *  ReadTransforms
 *  Read a set of transforms from a string and transfer it into a file
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
 *  RunTransformList
 *  Iterate through the list and execute the transforms in it
 *-----------------------------------------------------------------------------*/
void RunTransformList(TransformList *list)
{
    TransformNode* node = list->root;

    /* Verify the list */
    if(list->root == NULL)
        return;


    /* Iterate through the list */
    while(node != NULL)
    {
        RunTransform(node->data);
        node = node->next;
    }
}


/*-----------------------------------------------------------------------------
 *  CreateTransforms
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
    while(node != NULL)
    {
        /* Draw the shape */
        glLoadName(i);
        glPushMatrix( );
            glColor3f( 0.1, 0.0, 1.0 );
            if(selectedIndex == i)
            {
                glLoadIdentity( );
                glTranslatef( lastX, lastY, 0.0 );
                selectedNode = node;
                selectedList = list;
            }
            if(selectedNode == node)
                glColor3f( 1.0, 0.0, 1.0 );
            glCallList('t');
            glColor3f( 1.0, 1.0, 1.0 );

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
            glTranslatef( 17.5, 0.0, 0.0 );

        node = node->next;
        ++i;
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

    /* Store the coordinates */
    lastX = objX;
    lastY = objY;
    if(selectedIndex != 0)
    {
        /* Calculate the Delta */
        if((selectedIndex == HOUSE) && (selectedNode != NULL) && (selectedList == &tlSelectedTransforms))
        {
            Transform* t = selectedNode->data;
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
        glutPostRedisplay( );
    }
}

/*-----------------------------------------------------------------------------
 *  CompareMatrices
 *  Compares matrix a with matrix b and returns TRUE or FALSE if they are
 *  equivalent
 *-----------------------------------------------------------------------------*/
int CompareMatrices( GLdouble *a, GLdouble *b )
{
    int i = 0;

    /* Iterate through and compare each part of the matrix */
    for(i = 0; i < MATRIX_SIZE; ++i)
        if( fabs(a[i] - b[i]) > EPSILON )
            return FALSE;
    return TRUE;
}

/*-----------------------------------------------------------------------------
 *  ReadLevel
 *  Read in the level file and set up the next list
 *-----------------------------------------------------------------------------*/
void ReadLevel(FILE* file, char* buf)
{
    /* Read the level */
    fgets(buf, BUF_SIZ, file);
    if(!feof(file))
    {
        /* Create the levels */
        ReadTransforms(buf, &tlLevel);
        CopyList( &tlLevel, &tlAvailableTransforms );
    }
    else
        gameComplete = TRUE;
}
