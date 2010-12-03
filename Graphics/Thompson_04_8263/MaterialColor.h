#ifndef __MATERIAL_COLOR_H_
#define __MATERIAL_COLOR_H_
#include <GL/freeglut.h>
#include <cstring>
#define COLOR_SIZE 4

class MaterialColor
{
private:
	GLfloat specular[COLOR_SIZE];
	GLfloat ambient[COLOR_SIZE];
	GLfloat diffuse[COLOR_SIZE];
	GLfloat color[COLOR_SIZE];

	void SetColor(GLfloat*, GLfloat, GLfloat, GLfloat, GLfloat);
public:
	MaterialColor(void);
	~MaterialColor(void);
	void SetAmbientColor(GLfloat, GLfloat, GLfloat, GLfloat);
	void SetSpecularColor(GLfloat, GLfloat, GLfloat, GLfloat);
	void SetDiffuseColor(GLfloat, GLfloat, GLfloat, GLfloat); 
	void SetShapeColor(GLfloat, GLfloat, GLfloat, GLfloat);
	void SetAllColors(GLfloat, GLfloat, GLfloat, GLfloat);
	void GetMaterialColors(void);
};
#endif

