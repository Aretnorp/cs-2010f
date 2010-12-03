#ifndef __PICKING_H_
#define __PICKING_H_
#include <set>
namespace Picking
{
        int GetNextIndex(void);
	void AddSelectedIndex(int index);
	void RemoveSelectedIndex(int index);
	void RemoveAllSelected(void);
	bool IsSelectedIndex(int index);
	bool IsEmpty();
}
#endif
