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