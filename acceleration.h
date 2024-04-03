/***********************************************************************
 * Header File:
 *    ACCELERATION 
 * Author:
 *    Fabian Diaz Santiago and Josue Molina
 * Summary:
 *    Everything we need to know about acceleration
 ************************************************************************/


#pragma once

class TestAcceleration;
class TestVelocity;
class TestPosition;
class TestLander;
class Angle;
#include <cmath>
#include "angle.h"


/*********************************************
 * Acceleration
 * Let's get moving
 *********************************************/
class Acceleration
{
   friend TestPosition;
   friend TestVelocity;
   friend TestAcceleration;
   friend TestLander;

public:
   // constructors
   Acceleration()                       : ddx(0.0), ddy(0.0) { }
   Acceleration(double ddx, double ddy) : ddx(ddx), ddy(ddy) { }
   // extra:
   Acceleration(const Angle& angle, double magnitude)
       : ddx(sin(angle.getRadians())* magnitude), ddy(cos(angle.getRadians())* magnitude) { }


   // getters
   virtual double getDDX()   const           { return ddx; }
   virtual double getDDY()   const           { return ddy; }

   // setters
   virtual void setDDX(double ddx)           { this->ddx = ddx; }
   virtual void setDDY(double ddy)           { this->ddy = ddy; }
   virtual void set(const Angle & a, double magnitude);
   virtual void addDDX(double ddx) { setDDX(getDDX() + ddx); }
   virtual void addDDY(double ddy) { setDDY(getDDY() + ddy); }
   virtual void add(const Acceleration& rhs);

   // Overload the + operator.
   Acceleration operator+(const Acceleration& rhs) const
   {
       return Acceleration(this->ddx + rhs.ddx, this->ddy + rhs.ddy);
   }
   
private:
   double ddx;     // horizontal acceleration
   double ddy;     // vertical acceleration
};

#include <cassert>

/*********************************************
 * AccelerationDummy
 * A Dummy double for acceleration. This does nothing but assert.
 * Stubs will be derived from this for the purpose of making
 * isolated unit tests.
 *********************************************/
class AccelerationDummy : public Acceleration
{
public:
   // getters
   virtual double getDDX()   const { assert(false); return 99.9; }
   virtual double getDDY()   const { assert(false); return 99.9; }

   // setters
   virtual void setDDX(double ddx)           { assert(false); }
   virtual void setDDY(double ddy)           { assert(false); }
   virtual void set(const Angle& a, double magnitude);
   virtual void addDDX(double ddx)           { assert(false); }
   virtual void addDDY(double ddy)           { assert(false); }
   virtual void add(const Acceleration& rhs) { assert(false); }
};
