/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    Fabian Diaz Santiago and Josue Molina
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"
#include "howitzer.h"
#include "ground.h"
#include "projectile.h"
#include "uiInteract.h" 
#include "uiDraw.h" 

 /*********************************************
   * STATUS
   * What is the status of the simulator?
   *********************************************/
enum Status {READY, FLYING, VICTORY};

 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
    Simulator(const Position& posUpperRight) : interval(0.5), posUpperRight(posUpperRight), status(READY), simulationTime(0.0), ground(posUpperRight) { reset(); }

    void reset()
    {
        status = READY;
        howitzer.generatePosition(posUpperRight);
        projectile.reset();
        ground.reset(howitzer.getPosition());
    }
   
    void fire();

    void display(ogstream& gout);

    void advance();

    bool input(const Interface* pUI);

    // configure the simulator

    void setInterval(double interval) { this->interval = interval; }

    void setMass(double mass) { projectile.setMass(mass); }
    void setDiameter(double diameter) { projectile.setRadius(diameter / 2.0);  }


private:
    // did projectile hit the target?
    bool hitTarget() const
    {
        if (!projectile.flying())
            return false;
        return abs(projectile.getPosition().getPixelsX() - ground.getTarget().getPixelsX()) <= 5.0;
    }

    double getHeightMeters(const Position& posProjectile) const
    {
        double altitudeProjectile = posProjectile.getMetersY();
        double altitudeGround = ground.getElevationMeters(posProjectile);
        double heighMeters = altitudeProjectile - altitudeGround;
        return heighMeters;
    }

    Howitzer howitzer;
    Ground ground;
    Position posUpperRight;
    Status status = READY;
    double interval;
    double simulationTime;
    Projectile projectile;
};
