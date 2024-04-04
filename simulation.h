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
#define TIME_INTERVAL 0.5



 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
    Simulator(const Position& posUpperRight):  ground(posUpperRight), simulationTime(0.0)
    {
        // reset the game
        howitzer.generatePosition(posUpperRight);
        ground.reset(howitzer.getPosition());
        projectile.reset();
    }

    void displayStatistics() const
    {
        // Assuming your ogstream object is created correctly elsewhere in your code
        ogstream gout;

        // Set the position to display the statistics
        gout.setPosition(Position(22000, 17400)); 

        // Display the statistics
        gout << "Altitude: " << projectile.getPosition().getMetersY() << "m\n";
        gout << "Speed: " << projectile.getSpeed() << "m/s\n";
        gout << "Distance: " << projectile.getFlightDistance() << "m\n";
        gout << "Hang Time: " << projectile.getFlightTime() << "s\n";

    }


    void draw(ogstream& gout) const
    {
        ground.draw(gout); // Draw the ground
        howitzer.draw(gout, flightTime); // Draw the howitzer

        // Draw the projectile if it's flying
        if (projectile.flying())
        {
            projectile.draw(gout);
        }
      
        displayStatistics();
    }

    // input 
    Howitzer input(const Interface* pUI)
    {
        howitzer.input(pUI);

        // Fire the gun
        if (!projectile.flying() && pUI->isSpace())
        {
            projectile.fire(howitzer.getPosition(), simulationTime, howitzer.getElevation(), howitzer.getMuzzleVelocity());
        }

        // Update the simulation time
        simulationTime += TIME_INTERVAL;

        // Advance the projectile
        projectile.advance(simulationTime);

        // check if colission
        if (projectile.getPosition().getMetersY() < ground.getElevationMeters(projectile.getPosition()))
        {
            projectile.reset();
        }

        // check if hit target
        if (projectile.flying())
        {
            if (this->ground.getTarget().getPixelsX() == projectile.getPosition().getPixelsX())
            {   
                // Projectile has hit the target
                std::cout << "Target Hit!\n";
                projectile.reset();
                ground.reset(howitzer.getPosition());
            }
        }

        // End the game when 'q' is pressed
        if (pUI->isQ())
        {
            exit(0);
        }

        return howitzer;
    }


private:
    Howitzer howitzer;
    Ground ground;
    double flightTime;
    double simulationTime;
    Projectile projectile;
};
