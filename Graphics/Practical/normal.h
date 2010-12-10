/*
 * =====================================================================================
 *
 *       Filename:  normal.h
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
#include <math.h>

#define X 0
#define Y 1
#define Z 2

float *UnitNormal(     float pointAx, float pointAy, float pointAz,
                       float pointBx, float pointBy, float pointBz,
                       float pointCx, float pointCy, float pointCz );

void GetSmoothNormals(float x, float y, float z);
