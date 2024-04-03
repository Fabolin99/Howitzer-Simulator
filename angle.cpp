/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Fabian Diaz Santiago and Josue Molina
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>
using namespace std;

/************************************
 * ANGLE : NORMALIZE
 ************************************/
double Angle::normalize(double radians) const
{
    if (radians >= (M_PI * 2.0))
    {
        double multiple = floor(radians / (M_PI * 2.0));
        return radians - ((M_PI * 2.0) * multiple);
    }
    else if (radians < 0.0)
    {
        double multiples = ceil(-radians / (M_PI * 2.0));
        return (M_PI * 2.0) * multiples + radians;
    }
    return radians;
}



