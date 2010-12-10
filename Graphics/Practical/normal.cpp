/* FUNCTION:  UnitNormal

  At the top of your program:

  #include <math.h>  // You are using sqrt!

  #define X 0
  #define Y 1
  #define Z 2

  Remember to:
  glEnable( GL_NORMALIZE );

  call the function like:

  glNormal3fv( UnitNormal(-1,  1, 1,
                          -1, -1, 1,
                           1, -1, 1 ));

*/

#include "normal.h" // You are using sqrt!

#define X 0
#define Y 1
#define Z 2

/**************************************************************************/
/* Returns the Normal of two vectors with magnitude 1                     */
/**************************************************************************/        
float *UnitNormal(     float pointAx, float pointAy, float pointAz,
                       float pointBx, float pointBy, float pointBz,
                       float pointCx, float pointCy, float pointCz )
{
#define SQR(A) ((A)*(A))
    static float vectorC[3];
    float unitScale;
    float vectorAx, vectorAy, vectorAz;
    float vectorBx, vectorBy, vectorBz;

    vectorAx = pointBx - pointAx;
    vectorAy = pointBy - pointAy;
    vectorAz = pointBz - pointAz;

    vectorBx = pointCx - pointAx;
    vectorBy = pointCy - pointAy;
    vectorBz = pointCz - pointAz;

    vectorC[X] = vectorAy * vectorBz - vectorAz * vectorBy;
    vectorC[Y] = vectorAz * vectorBx - vectorAx * vectorBz;
    vectorC[Z] = vectorAx * vectorBy - vectorAy * vectorBx;

    unitScale = sqrt( SQR(vectorC[X]) + SQR(vectorC[Y]) + SQR(vectorC[Z]) );
    vectorC[X] /= unitScale;
    vectorC[Y] /= unitScale;
    vectorC[Z] /= unitScale;

    return( vectorC );

#undef SQR
}

void CalculateSmoothNormal(float x, float y, float z)
{
    /* Calculate the normal */
    float normal = sqrtf((x * x) + (y * y) + (z * z));

    /* Determine the directional vectors */
    glNormal3f(x / normal, y / normal, z / normal);
}

