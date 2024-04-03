/***********************************************************************
 * Source File:
 *    ACCELERATION 
 * Author:
 *    Fabian Diaz Santiago and Josue Molina
 * Summary:
 *    Everything we need to know about changing speed
 ************************************************************************/

#include "acceleration.h"
#include "angle.h"

#include <cmath>

 /*********************************************
  * ACCELERATION : ADD
  *********************************************/
void Acceleration::add(const Acceleration& a)
{
	ddx += a.getDDX();
	ddy += a.getDDY();
}

/*********************************************
 * ACCELERATION : SET
 *  set from angle and direction
 *********************************************/
void Acceleration::set(const Angle & a, double magnitude)
{
   ddx = magnitude * sin(a.getRadians());
   ddy = magnitude * cos(a.getRadians());
}
void AccelerationDummy::set(const Angle& a, double magnitude)
{
   assert(false);
}
