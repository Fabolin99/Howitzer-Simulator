/**********************************************************************
 * Header File:
 *    HOWITZER
 * Author:
 *    Fabian Diaz Santiago and Josue Molina
 * Summary:
 *    Everything we need to know about a howitzer (aka the gun)
 ************************************************************************/

#pragma once

#include <list>
#include "angle.h"
#include "position.h"
#include "velocity.h"
#include "physics.h"
#include "uiDraw.h"
#include "uiInteract.h"



#define DEFAULT_MUZZLE_VELOCITY   827.00     // m/s


class TestHowitzer;

 /*********************************************
  * Howitzer
  * Everything we need to know about a howitzer (aka the gun)
  *********************************************/
class Howitzer
{
   public:
      // for unit tests
      friend ::TestHowitzer;

      // default constructor
      Howitzer() : muzzleVelocity(DEFAULT_MUZZLE_VELOCITY), elevation(45.0) {}

      // draw
      void draw(ogstream& gout, double flightTime) const
      {
         gout.drawHowitzer(position,
            elevation.getRadians(),
            flightTime);
      }

      // where is the howitzer at right now?
      Position & getPosition() { return position; }

      // generate a new position for the howitzer
      void generatePosition(const Position& posUpperRight)
      {
         double xPixels = random(posUpperRight.getPixelsX() * 0.1,
            posUpperRight.getPixelsX() * 0.9);
         position.setPixelsX(xPixels);
         position.setPixelsY(0);
      }

      // get the muzzle velocity
      double getMuzzleVelocity() const { return muzzleVelocity; }

      // move the angle of the howitzer
      void rotate(double radian) { elevation.add(radian); }

      // raise (or lower) the howitzer
      void raise(double radian)
      {
         elevation.add(elevation.isRight() ? -radian : radian);
      }

      // get the elevation
      const Angle & getElevation() const { return elevation; }

      // extra:

      void input(const Interface* pUI) {
          // Rotate right
          if (pUI->isRight()) {
              rotate(0.05);
          }

          // Rotate left
          if (pUI->isLeft()) {
              rotate(-0.05);
          }

          // Raise
          if (pUI->isUp()) {
              raise(0.03);
          }

          // Lower
          if (pUI->isDown()) { // this is wrong
              raise(-0.03);
          }
      }

  
   private:
      Position position;      // initial position of the projectile
      double muzzleVelocity;  // muzzle velocity, defaults to 827.0 m/s
      Angle elevation;        // the elevation of the howitzer where 0 is up and positive is right.
};