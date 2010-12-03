/*
 * =====================================================================================
 *
 *       Filename:  Picking.cpp
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
#include "Picking.h"

int index = 1;
std::set<int> selected;

/*-----------------------------------------------------------------------------
*  GetNextIndex
*  Gets the available Index for picking
*-----------------------------------------------------------------------------*/
int Picking::GetNextIndex(void)
{
    return index++;
}

/*-----------------------------------------------------------------------------
*  AddSelectedIndex
*  Adds a new Index to the selected Set
*-----------------------------------------------------------------------------*/
void Picking::AddSelectedIndex(int index)
{
	selected.insert(index);
}

/*-----------------------------------------------------------------------------
*  RemoveSeletedIndex
*  Adds a remove Index to the selected Set
*-----------------------------------------------------------------------------*/
void Picking::RemoveSelectedIndex(int index)
{
	selected.erase(index);
}

/*-----------------------------------------------------------------------------
*  RemoveAllSelected
*  Clears the seleted set
*-----------------------------------------------------------------------------*/
void Picking::RemoveAllSelected(void)
{
	selected.clear( );
}

/*-----------------------------------------------------------------------------
*  IsSelectedIndex
*  Determines if a selected Index is empty
*-----------------------------------------------------------------------------*/
bool Picking::IsSelectedIndex(int index)
{
	return (selected.find(index) != selected.end());
}

/*-----------------------------------------------------------------------------
*  IsEmpty
*  Indicates whether or not the selected set is empty
*-----------------------------------------------------------------------------*/
bool Picking::IsEmpty()
{
	return selected.empty();
}