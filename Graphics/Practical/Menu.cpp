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
bool lightMode = false;
bool globalLight = false;
bool positionalLight = false;

Transformations transforms;

/*-----------------------------------------------------------------------------
*  CreateMiddleMenu
*  Creates the Middle-Click menu and adds the necessary entries
*-----------------------------------------------------------------------------*/
void CreateMiddleMenu()
{
    /* Create the Sub Menu */
    int interactiveMode = glutCreateMenu(Menu);
    glutAddMenuEntry("1. Rotate", MENU_ROTATE);
    glutAddMenuEntry("2. Translate", MENU_TRANSLATE);
    glutAddMenuEntry("3. Scale", MENU_SCALE);

    int lightMode = glutCreateMenu(Menu);
    glutAddMenuEntry("1. Global Light", MENU_GLOBAL);
    glutAddMenuEntry("2. Positional Light", MENU_POSITIONAL);

    /* Create the Main Menu */
    glutCreateMenu(Menu);
    glutAddSubMenu("1. Interactive", interactiveMode);
    glutAddSubMenu("2. Light", lightMode);
    glutAddMenuEntry("3. Reset", MENU_RESET);
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
    case MENU_ROTATE:
        transforms.SetType(ROTATE); break;
    case MENU_TRANSLATE:
        transforms.SetType(TRANSLATE); break;
    case MENU_SCALE:
        transforms.SetType(SCALE); break;

    case MENU_GLOBAL:
        if(globalLight)
        {
            /* Disable the positional */
            if(positionalLight) positionalLight = false;
            globalLight = false;
        }
        else
            globalLight = true;
        break;

    case MENU_POSITIONAL:
        if(globalLight)
            positionalLight = !positionalLight;
        break;

    case MENU_RESET:
        Reset( ); break;

    case MENU_EXIT:
        exit(EXIT_SUCCESS); break;

    }

    /* Update the display */
    glutPostRedisplay( );
}
