/*
 * =====================================================================================
 *
 *       Filename:  Menu.h
 *
 *    Description:  Creates a Puppet model that can be modified via the joints
 *
 *        Version:  1.0
 *        Created:  November 30th, 2010
 *
 *         Author:  Cody Thompson
 * =====================================================================================
 */
#ifndef __MENU_H_
#define __MENU_H_
#include <GL/freeglut.h>
#include "main.h"
#include "Transformations.h"

enum MENU_TYPE
{
    MENU_ROTATE,
    MENU_TRANSLATE,
    MENU_SCALE,
    MENU_GLOBAL,
    MENU_POSITIONAL,
    MENU_RESET,
    MENU_EXIT,
};


extern bool positionMode;
extern bool lightMode;
extern bool globalLight;
extern bool positionalLight;

extern Transformations transforms;

void CreateMiddleMenu();
void Menu(int);
#endif
