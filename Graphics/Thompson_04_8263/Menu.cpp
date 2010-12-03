/*
 * =====================================================================================
 *
 *       Filename:  Menu.cpp
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
#include "Menu.h"

bool positionMode = true;
bool jointMode = false;
bool resetMode = false;
bool lightMode = false;
bool flatShade = true;


/*-----------------------------------------------------------------------------
*  CreateMiddleMenu
*  Creates the Middle-Click menu and adds the necessary entries
*-----------------------------------------------------------------------------*/
void CreateMiddleMenu()
{
	/* Create the Sub Menu */
	int fillMode = glutCreateMenu(Menu);
	glutAddMenuEntry("1. On / Off", MENU_ON_OFF);
	glutAddMenuEntry("2. Flat / Smooth", MENU_FLAT_SMOOTH);

	/* Create the Main Menu */
	glutCreateMenu(Menu);
	glutAddMenuEntry("1. Position / Orientation", MENU_POS);
	glutAddMenuEntry("2. Joints", MENU_JOINTS);
	glutAddMenuEntry("3. Reset", MENU_RESET);
	glutAddSubMenu("4. Light", fillMode);
	glutAddMenuEntry("5. Exit", MENU_EXIT);

	/* Attach the menu */
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
}

/*-----------------------------------------------------------------------------
*  Menu
*  Handles when a Menu selection has been made by the user
*-----------------------------------------------------------------------------*/
void Menu(int item)
{
	switch(item)
	{
    	case MENU_POS: 
			positionMode = !positionMode; break;
    	case MENU_JOINTS: 
			jointMode = !jointMode; 
			Picking::RemoveAllSelected();
			break;
    	case MENU_RESET: 
			resetMode = !resetMode;
			Picking::RemoveAllSelected();
			Reset( );
			break;
    	case MENU_ON_OFF: 
			lightMode = !lightMode; break;
    	case MENU_FLAT_SMOOTH: 
			flatShade = !flatShade; break;
    	case MENU_EXIT: 
			exit(EXIT_SUCCESS); break;
	}

	/* Update the display */
	glutPostRedisplay( );
}
