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

enum MENU_TYPE
{
    MENU_POS,
    MENU_JOINTS,
    MENU_RESET,
    MENU_ON_OFF,
    MENU_FLAT_SMOOTH,
    MENU_EXIT,
};

extern bool positionMode;
extern bool resetMode;
extern bool lightMode;
extern bool flatShade;

void CreateMiddleMenu();
void Menu(int);
#endif
