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
#include "Transformations.h"
#include <stdio.h>

/*-----------------------------------------------------------------------------
*  Transform
*  Constructor
*-----------------------------------------------------------------------------*/
Transformations::Transformations(void)
{
    this->Reset( );
    this->currentTransform = &(this->rotate);
}

/*-----------------------------------------------------------------------------
*  ~Transform
*  Destructor
*-----------------------------------------------------------------------------*/
Transformations::~Transformations(void)
{

}

/*-----------------------------------------------------------------------------
*  GetTransformations
*  Gets the Transformations (all)
*-----------------------------------------------------------------------------*/
void Transformations::GetTransformations(void)
{
    this->GetTranslate( );
    this->GetRotation( );
    this->GetScale( );
}

/*-----------------------------------------------------------------------------
*  GetRotation
*  Gets the Rotation
*-----------------------------------------------------------------------------*/
void Transformations::GetRotation(void)
{
    glRotatef(this->rotate.x, 1.0, 0.0, 0.0);
    glRotatef(this->rotate.y, 0.0, 1.0, 0.0);
    glRotatef(this->rotate.z, 0.0, 0.0, 1.0);
}

/*-----------------------------------------------------------------------------
*  GetScale
*  Gets the Scale
*-----------------------------------------------------------------------------*/
void Transformations::GetScale(void)
{
    glScalef(this->scale.x, this->scale.y, this->scale.z);
}

/*-----------------------------------------------------------------------------
*  GetTranslate
*  Gets the translation
*-----------------------------------------------------------------------------*/
void Transformations::GetTranslate(void)
{
    glTranslatef(this->translate.x, this->translate.y, this->translate.z);
}

/*-----------------------------------------------------------------------------
*  SetType
*  Sets the current Transform for selection
*-----------------------------------------------------------------------------*/
void Transformations::SetType(TRANSLATE_TYPE type)
{
    switch(type)
    {
        case TRANSLATE:
            this->currentTransform = &(this->translate); break;
        case SCALE:
            this->currentTransform = &(this->scale); break;
        case ROTATE:
            this->currentTransform = &(this->rotate); break;
    }
    this->type = type;
}

/*-----------------------------------------------------------------------------
*  SetX
*  Sets the X attribute of current transform
*-----------------------------------------------------------------------------*/
void Transformations::SetX( float x )
{
    if((type == TRANSLATE) || (type == SCALE))
        this->currentTransform->x += (x / 100);
    else
        this->currentTransform->x += x;
}

/*-----------------------------------------------------------------------------
*  SetY
*  Sets the Y attribute of current transform
*-----------------------------------------------------------------------------*/
void Transformations::SetY( float y )
{
    if((type == TRANSLATE) || (type == SCALE))
        this->currentTransform->y += y / 100;
    else
        this->currentTransform->y += y;
}

/*-----------------------------------------------------------------------------
*  SetZ
*  Sets the Z attribute of current transform
*-----------------------------------------------------------------------------*/
void Transformations::SetZ( float z )
{
    if((type == TRANSLATE) || (type == SCALE))
        this->currentTransform->z += z / 100;
    else
        this->currentTransform->z += z;
}

/*-----------------------------------------------------------------------------
*  Reset
*  Resets the transformations
*-----------------------------------------------------------------------------*/
void Transformations::Reset( void )
{
    this->scale.x = this->scale.y = this->scale.z = 1;
    this->translate.x = this->translate.y = this->translate.z = 0;
    this->rotate.x = this->rotate.y = this->rotate.z = 0;
}
