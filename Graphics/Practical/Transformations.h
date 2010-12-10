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
#include <GL/freeglut.h>

typedef struct Transform
{
    float x;
    float y;
    float z;
} Transform;

enum TRANSLATE_TYPE
{
    ROTATE,
    TRANSLATE,
    SCALE
};

class Transformations
{
private:
    Transform scale;
    Transform translate;
    Transform rotate;
    Transform* currentTransform;
    TRANSLATE_TYPE type;
public:
    Transformations( );
    ~Transformations( );

    void GetTransformations( void );
    void SetType(TRANSLATE_TYPE type);

    void SetX( float x );
    void SetY( float y );
    void SetZ( float z );

    void GetTranslate( void );
    void GetRotation( void );
    void GetScale( void );

    void Reset( void );
};
