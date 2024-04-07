/**********************************************************************
 * Header File:
 *    PROJECTILE
 * Author:
 *    Fabian Diaz Santiago and Josue Molina
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/

#pragma once

#include <list>
#include "position.h"
#include "velocity.h"
#include "physics.h"
#include "uiDraw.h"

#define DEFAULT_PROJECTILE_WEIGHT 46.7       // kg
#define DEFAULT_PROJECTILE_RADIUS 0.077545   // m

// forward declaration for the unit test class
class TestProjectile; 

 /**********************************************************************
  * Projectile
  *    Everything we need to know about a projectile
  ************************************************************************/
class Projectile
{
public:
   // Friend the unit test class
   friend ::TestProjectile;

   // create a new projectile with the default settings
   Projectile() : mass(DEFAULT_PROJECTILE_WEIGHT), radius(DEFAULT_PROJECTILE_RADIUS) {}

   // reset 
   void reset()
   {
       // Clear the flight path
       flightPath.clear();
       // Reset the member variables to their default values
       mass = DEFAULT_PROJECTILE_WEIGHT;
       radius = DEFAULT_PROJECTILE_RADIUS;
   }

   // extra:
   bool hasCollided() const { return collided; }

   // Let the shell know it has colided with something.
   void collision() { collided = true; }

   // True if the shell has been fires without being reset, false otherwise.
   bool hasFired() const { return isFired; }

   void fired() { isFired = true; }





   void draw(ogstream& gout) const
   {
       for (auto it = flightPath.cbegin(); it != flightPath.cend(); ++it)
           gout.drawProjectile(it->pos, currentTime() - it->t);
   }

   bool flying() const { return !flightPath.empty(); }

   double getAltitude() const { return flying() ? flightPath.back().pos.getMetersY() : 0; }

   Position getPosition() const { return flying() ? flightPath.back().pos : Position(); }

   double getFlightTime() const { return flightPath.size() >= 2 ? flightPath.back().t - flightPath.front().t : 0.0; }

   double getFlightDistance() const 
   {
       return (flightPath.size() >= 2) ?
           abs(flightPath.front().pos.getMetersX() - flightPath.back().pos.getMetersX()) : 0.0;
   }

   double getSpeed() const { return flying() ? flightPath.back().v.getSpeed() : 0.0; }

   double currentTime() const { return flying() ? flightPath.back().t : 0.0; }

   void setMass(double mass) { this->mass = mass; }

   void setRadius(double radius) { this->radius; }

   void fire(const Position& posHowitzer, double simulationTime, const Angle& elevation, double muzzleVelocity);

   // advance the round forward until the next unit of time
   void advance(double simulationTime);

private:

   // keep track of one moment in the path of the projectile
   struct PositionVelocityTime
   {
      PositionVelocityTime() : pos(), v(), t(0.0) {}
      Position pos;
      Velocity v;
      double t;
   };

   double mass;           // weight of the M795 projectile. Defaults to 46.7 kg
   double radius;         // radius of M795 projectile. Defaults to 0.077545 m
   std::list<PositionVelocityTime> flightPath;
   bool collided = false; // extra
   bool isFired = false;

};