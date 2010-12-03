#ifndef __HEAD_H_
#define __HEAD_H_
#include "Shape.h"
#include "Square.h"

class Head :
	public Shape
{
private:
	int size;
	int index;
	Square* head;
	void LoadTexture(char*, int);
public:
	Head(int size, RotationLimits* = new RotationLimits());
	~Head(void);

	void Draw();
	void RotateObject(int, int);
};
#endif

