#include "MaterialColor.h"


/*-----------------------------------------------------------------------------
 *  MaterialColor
 *  Creates a MaterialColor object with default values of White
 *-----------------------------------------------------------------------------*/
MaterialColor::MaterialColor(void)
{
	// Create each of the coloring structs
	this->SetAllColors(1.0, 1.0, 1.0, 1.0);
}

/*-----------------------------------------------------------------------------
 *  ~MaterialColor
 *  Destroys a MaterialColor object
 *-----------------------------------------------------------------------------*/
MaterialColor::~MaterialColor(void)
{
}

/*-----------------------------------------------------------------------------
 *  SetColor
 *  Sets the color of a given array to a color
 *-----------------------------------------------------------------------------*/
void MaterialColor::SetColor(GLfloat* color, GLfloat r,
							 GLfloat g, GLfloat b,
							 GLfloat a)
{
	// Create the array
	GLfloat* newColor = new GLfloat[COLOR_SIZE];
	newColor[0] = r;
	newColor[1] = g;
	newColor[2] = b;
	newColor[3] = a;

	// Set the color
	memcpy(color, newColor, sizeof(GLfloat[COLOR_SIZE]));

	// Free the memory
	delete newColor;
}

/*-----------------------------------------------------------------------------
 *  SetAmbientColor
 *  Sets the Ambient color to a given set of RGBA values
 *-----------------------------------------------------------------------------*/
void MaterialColor::SetAmbientColor(GLfloat r, GLfloat g,
									GLfloat b, GLfloat a)
{
	this->SetColor(this->ambient, r, g, b, a);
}

/*-----------------------------------------------------------------------------
 *  SetSpecularColor
 *  Sets the Specular color to a given set of RGBA values
 *-----------------------------------------------------------------------------*/
void MaterialColor::SetSpecularColor(GLfloat r, GLfloat g,
									GLfloat b, GLfloat a)
{
	this->SetColor(this->specular, r, g, b, a);
}

/*-----------------------------------------------------------------------------
 *  SetDiffuseColor
 *  Sets the Diffuse color to a given set of RGBA values
 *-----------------------------------------------------------------------------*/
void MaterialColor::SetDiffuseColor(GLfloat r, GLfloat g,
									GLfloat b, GLfloat a)
{
	this->SetColor(this->diffuse, r, g, b, a);
}

/*-----------------------------------------------------------------------------
 *  SetShapeColor
 *  Sets the Shape color to a given set of RGBA values
 *-----------------------------------------------------------------------------*/
void MaterialColor::SetShapeColor(GLfloat r, GLfloat g,
							      GLfloat b, GLfloat a)
{
	this->SetColor(this->color, r, g, b, a);
}

/*-----------------------------------------------------------------------------
 *  SetAllColors
 *	Sets All the colors to a given set of RGBA values 
 *-----------------------------------------------------------------------------*/
void MaterialColor::SetAllColors(GLfloat r, GLfloat g,
								 GLfloat b, GLfloat a)
{
	this->SetColor(this->ambient, r, g, b, a);
	this->SetColor(this->specular, r, g, b, a);
	this->SetColor(this->diffuse, r, g, b, a);
	this->SetColor(this->color, r, g, b, a);
}

/*-----------------------------------------------------------------------------
 *  GetMaterialColors
 *  Calls the necessary functions to set the Material and Color
 *	values in the Pipeline
 *-----------------------------------------------------------------------------*/
void MaterialColor::GetMaterialColors(void)
{
	// Set the Material color
	glMaterialfv(GL_FRONT, GL_SPECULAR, this->specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, this->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, this->diffuse);
	glMaterialf (GL_FRONT, GL_SHININESS, 15 );

	// Set the Shape color
	glColor4f(color[0], color[1], color[2], color[3]);
}