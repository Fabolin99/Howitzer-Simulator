/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    Fabian Diaz Santiago and Josue Molina
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/


 #include "projectile.h"
 #include "angle.h"
#include "acceleration.h"
 using namespace std;

 /************************************
 * PROJECTILE : FIRE
 ************************************/
 void Projectile::fire(const Position& posHowitzer, 
     double simulationTime, const Angle& elevation, 
     double muzzleVelocity) 
 {
     reset();

     PositionVelocityTime pvt;
     pvt.pos = posHowitzer;
     pvt.t = simulationTime;
     pvt.v.set(elevation, muzzleVelocity);
     flightPath.push_back(pvt);
 }

 /************************************
* PROJECTILE : ADVANCE
************************************/
 void Projectile::advance(double simulationTime)
 {
     // check if flying
     if (!flying())
         return;

     PositionVelocityTime pvt = flightPath.back();
     double speed = pvt.v.getSpeed();
     double altitude = pvt.pos.getMetersY();
     double interval = simulationTime - currentTime();
     assert(interval > 0.0);

     // compute acceleration 
     double density = densityFromAltitude(altitude);
     double speedSound = speedSoundFromAltitude(altitude);
     double mach = speed / speedSound;
     double dragCoefficient = dragFromMach(mach);
     double windResistence = forceFromDrag(density, dragCoefficient, radius, speed);
     double magnitudeWind = accelerationFromForce(windResistence, mass);
     Acceleration aWind(-pvt.v.getAngle(), magnitudeWind); 
     
     // compute acceleration
     double magnitudeGravity = gravityFromAltitude(altitude);
     Angle angleGravity;
     angleGravity.setDown();
     Acceleration aGravity(angleGravity, magnitudeGravity); 

     // compute total acceleration
     Acceleration aTotal = aGravity + aWind; 

     // update position, velocity, and time
     pvt.pos.add(aTotal, pvt.v, interval);
     pvt.v.add(aTotal, interval);
     pvt.t = simulationTime;

     // add to the back of the flight path
     flightPath.push_back(pvt);
 }
