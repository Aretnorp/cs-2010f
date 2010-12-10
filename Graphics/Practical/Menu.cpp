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
    glutAddMenuEntry("2. Reset", MENU_RESET);
    glutAddSubMenu("3. Light", fillMode);
    glutAddMenuEntry("4. Exit", MENU_EXIT);

    /* Attach the menu */
    glutAttachMenu(GLUT_RIGHT_BUTTON);
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

    case MENU_RESET:
        resetMode = !resetMode;
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
