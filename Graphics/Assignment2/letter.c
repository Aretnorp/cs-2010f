/*
 * =====================================================================================
 *
 *       Filename:  letter.c
 *
 *    Description:  Defines a letter in 3D using GL Primitives
 *
 *        Version:  1.0
 *
 *         Author:  Cody Thompson
 *
 *     Difficulty:  The most difficult aspect was creating the proper perspective. Due
 *                  to the differences between the Projection Matrix and ModelView
 *                  Matrix, I had to learn how to do the proper implementation.
 *     Objectives:  Create an object in 3D using GL Primitives. Render the object in
 *                  3D. Use a proper perspective that shows the shape as a 3D object.
 * =====================================================================================
 */
/*-----------------------------------------------------------------------------
 *  Include the headers
 *-----------------------------------------------------------------------------*/
#include "letter.h"

/*-----------------------------------------------------------------------------
 *  InitShapes
 *  Creates and defines the ModelLists for the ShapeLists
 *-----------------------------------------------------------------------------*/
void InitShapes ( )
{
    /* Create a List */
    tLists = glGenLists(NUM_LISTS);

    /* Define the List */
    glNewList( 't', GL_COMPILE );

        /* Draw the Front Face */
        glColor3f(1.0, 0.0, 0.0);
        glBegin( GL_POLYGON );
            glVertex3f( -10.0, 30.0, 12.5 );
            glVertex3f( -10.0,-50.0, 12.5 );
            glVertex3f(  10.0,-50.0, 12.5 );
            glVertex3f(  10.0, 30.0, 12.5 );
            glVertex3f(  37.5, 30.0, 12.5 );
            glVertex3f(  37.5, 50.0, 12.5 );
            glVertex3f( -37.5, 50.0, 12.5 );
            glVertex3f( -37.5, 50.0, 12.5 );
            glVertex3f( -37.5, 30.0, 12.5 );
        glEnd( );

        /* Draw the Back Face */
        glColor3f(0.0, 1.0, 0.0);
        glBegin( GL_POLYGON );
            glVertex3f(  10.0, 30.0,-12.5 );
            glVertex3f(  10.0,-50.0,-12.5 );
            glVertex3f( -10.0,-50.0,-12.5 );
            glVertex3f( -10.0, 30.0,-12.5 );
            glVertex3f( -37.5, 30.0,-12.5 );
            glVertex3f( -37.5, 50.0,-12.5 );
            glVertex3f(  37.5, 50.0,-12.5 );
            glVertex3f(  37.5, 30.0,-12.5 );
        glEnd( );

        /* Draw the Inner Sides */
        glColor3f(0.0, 0.0, 1.0);
        glBegin( GL_QUAD_STRIP );
            glVertex3f(  37.5, 50.0,-12.5 );
            glVertex3f(  37.5, 50.0, 12.5 );
            glVertex3f(  37.5, 30.0,-12.5 );
            glVertex3f(  37.5, 30.0, 12.5 );
            glVertex3f(  10.0, 30.0,-12.5 );
            glVertex3f(  10.0, 30.0, 12.5 );
            glVertex3f(  10.0,-50.0,-12.5 );
            glVertex3f(  10.0,-50.0, 12.5 );
            glVertex3f( -10.0,-50.0,-12.5 );
            glVertex3f( -10.0,-50.0, 12.5 );
            glVertex3f( -10.0, 30.0,-12.5 );
            glVertex3f( -10.0, 30.0, 12.5 );
            glVertex3f( -37.5, 30.0,-12.5 );
            glVertex3f( -37.5, 30.0, 12.5 );
            glVertex3f( -37.5, 50.0,-12.5 );
            glVertex3f( -37.5, 50.0, 12.5 );
            glVertex3f(  37.5, 50.0,-12.5 );
            glVertex3f(  37.5, 50.0, 12.5 );
        glEnd( );

    /* End the List */
    glEndList( );

    /* Define the List */
    glNewList( 'T', GL_COMPILE );
        /* Draw the front faces */
        glColor3f(1.0, 0.0, 0.0);
        glBegin( GL_POLYGON );
            glVertex3f( -10.0, 30.0, 8.0 );
            glVertex3f( -10.0,-50.0, 8.0 );
            glVertex3f(  10.0,-50.0, 8.0 );
            glVertex3f(  10.0, 30.0, 8.0 );
        glEnd( );
        glBegin( GL_POLYGON );
            glVertex3f( -37.5, 50.0, 12.5 );
            glVertex3f( -37.5, 30.0, 12.5 );
            glVertex3f(  37.5, 30.0, 12.5 );
            glVertex3f(  37.5, 50.0, 12.5 );
        glEnd( );

        /* Draw the back faces */
        glColor3f(0.0, 1.0, 0.0);
        glBegin( GL_POLYGON );
            glVertex3f(  10.0, 30.0,-8.0 );
            glVertex3f(  10.0,-50.0,-8.0 );
            glVertex3f( -10.0,-50.0,-8.0 );
            glVertex3f( -10.0, 30.0,-8.0 );
        glEnd( );
        glBegin( GL_POLYGON );
            glVertex3f(  37.5, 50.0,-12.5 );
            glVertex3f(  37.5, 30.0,-12.5 );
            glVertex3f( -37.5, 30.0,-12.5 );
            glVertex3f( -37.5, 50.0,-12.5 );
        glEnd( );

        /* Draw the Top of the T */
        glColor3f(0.0, 0.0, 1.0);
        glBegin( GL_QUAD_STRIP );
            glVertex3f( -37.5, 30.0,-12.5 );
            glVertex3f( -37.5, 30.0, 12.5 );
            glVertex3f( -37.5, 50.0,-12.5 );
            glVertex3f( -37.5, 50.0, 12.5 );
            glVertex3f(  37.5, 50.0,-12.5 );
            glVertex3f(  37.5, 50.0, 12.5 );
            glVertex3f(  37.5, 30.0,-12.5 );
            glVertex3f(  37.5, 30.0, 12.5 );
        glEnd( );

        /* Draw the Bottom of the T */
        glColor3f(0.0, 0.0, 1.0);
        glBegin( GL_QUAD_STRIP );
            glVertex3f(  10.0, 30.0,-8.0 );
            glVertex3f(  10.0, 30.0, 8.0 );
            glVertex3f(  10.0,-50.0,-8.0 );
            glVertex3f(  10.0,-50.0, 8.0 );
            glVertex3f( -10.0,-50.0,-8.0 );
            glVertex3f( -10.0,-50.0, 8.0 );
            glVertex3f( -10.0, 30.0,-8.0 );
            glVertex3f( -10.0, 30.0, 8.0 );
        glEnd( );

        /* Draw the Underside of the T */
        glColor3f(0.0, 0.0, 1.0);
        glBegin( GL_QUAD_STRIP );
            glVertex3f( -37.5, 30.0,-12.5 );
            glVertex3f( -10.0, 30.0,-8.0 );
            glVertex3f( -37.5, 30.0, 12.5 );
            glVertex3f( -10.0, 30.0, 8.0 );
            glVertex3f(  37.5, 30.0, 12.5 );
            glVertex3f(  10.0, 30.0, 8.0 );
            glVertex3f(  37.5, 30.0,-12.5 );
            glVertex3f(  10.0, 30.0,-8.0 );
            glVertex3f( -37.5, 30.0,-12.5 );
            glVertex3f( -10.0, 30.0,-8.0 );
        glEnd( );
    /* End the List */
    glEndList( );
}
