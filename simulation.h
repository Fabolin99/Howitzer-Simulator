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
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
    Simulator(const Position& posUpperRight):  ground(posUpperRight) 
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
        projectile.draw(gout); // Draw the projectile

        displayStatistics();
    }

    // input 
    Howitzer input(const Interface* pUI)
    {
        howitzer.input(pUI);

        // fire the gun
        if (!projectile.flying() && pUI->isSpace())
        {
            projectile.fire(howitzer.getPosition(), simulationTime, howitzer.getElevation(), howitzer.getMuzzleVelocity());
        }

        // Advance the simulation time
        simulationTime += 0.1; // change?

        // End the game when 'q' is pressed
        if (pUI->isQ())
            exit(0);

        return howitzer;
    }


    // gameplay
    void gameplay(const Interface* pUI)
    {
        // Handle user input for the howitzer
        howitzer.input(pUI);

        // Fire the gun if space bar is pressed and the projectile is not already flying
        if (!projectile.flying() && pUI->isSpace())
        {
            projectile.fire(howitzer.getPosition(), simulationTime, howitzer.getElevation(), howitzer.getMuzzleVelocity());
        }

        // Update the simulation time
        simulationTime += 0.1; // Or use an appropriate time interval

        // Advance the projectile if it's flying
        if (projectile.flying())
        {
            projectile.advance(simulationTime);
        }

        // End the game if 'q' is pressed
        if (pUI->isQ())
        {
            exit(0);
        }
    }


private:
    Howitzer howitzer;
    Ground ground;
    double flightTime;
    double simulationTime;
    Projectile projectile;
};
