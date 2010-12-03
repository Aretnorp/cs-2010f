#ifndef __MENU_H_
#define __MENU_H_
#include <GL/freeglut.h>
#include "Picking.h"
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
extern bool jointMode;
extern bool resetMode;
extern bool lightMode;
extern bool flatShade;

void CreateMiddleMenu();
void Menu(int);
#endif