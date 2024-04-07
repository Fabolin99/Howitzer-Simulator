/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    Fabian Diaz Santiago and Josue Molina
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

 #include "simulation.h"  // for SIMULATION
#include <iomanip>

bool Simulator::input(const Interface* pUI)
{
	// move a lot
	if (pUI->isRight())
		howitzer.rotate(0.05);
	if (pUI->isLeft())
		howitzer.rotate(-0.05);

	// move a little
	if (pUI->isUp())
		howitzer.raise(0.003);
	if (pUI->isDown())
		howitzer.raise(-0.003);

	// fire the gun
	if (pUI->isSpace() && status == READY)
		status = FLYING;

	// quit the game
	if (pUI->isQ())
		return false; // exit!

	return true;
}

void Simulator::fire()
{
	// empty flight path
	projectile.fire(howitzer.getPosition(), simulationTime, howitzer.getElevation(), howitzer.getMuzzleVelocity());
	
	// change status
	status = FLYING;
}

void Simulator::advance()
{
	// advance time by one unit
	simulationTime += interval;

	// start a new path if there is not one
	if (!projectile.flying() && status == FLYING)
	{
		fire();
	}

	else if (status != FLYING)
	{
		if (!projectile.flying())
			return;
		if (simulationTime - projectile.currentTime() > 5.0)
			projectile.reset();
	}
	else
	{
		assert(status == FLYING);
		assert(projectile.flying());

		// advance the projectile
		projectile.advance(simulationTime);

		// did we land?
		if (getHeightMeters(projectile.getPosition()) < 0.0)
			status = hitTarget() ? VICTORY : READY;

		if (status == VICTORY)
		{
			// reset the game
			howitzer.generatePosition(posUpperRight);
			ground.reset(howitzer.getPosition());
			status = READY;
		}
	}
}

void Simulator::display(ogstream& gout)
{
	// draw the ground
	ground.draw(gout);

	// draw the path of the projectile in the air
	projectile.draw(gout);

	// draw the howitzer
	howitzer.draw(gout, projectile.flying() ? projectile.getFlightTime() : -1.0);

	// status text
	Position posStatus(posUpperRight);
	posStatus.addPixelsX(-120.0);
	posStatus.addPixelsY(-20.0);
	gout = posStatus;
	gout.setf(std::ios::fixed | std::ios::showpoint);
	gout.precision(1);
	if (status == FLYING && projectile.flying())
	{
		gout << "altitude:\n"
			<< "speed:\n"
			<< "distance:\n"
			<< "hang time:\n";
		posStatus = posUpperRight;
		posStatus.addPixelsX(-60.0);
		posStatus.addPixelsY(-20.0);
		gout = posStatus;
		gout << projectile.getAltitude() << "m\n";
		gout << projectile.getSpeed() << "m/s\n";
		gout << abs(projectile.getPosition().getMetersX() - howitzer.getPosition().getMetersX()) << "m\n";
		gout << projectile.getFlightTime() << "s\n";
	}
	else
	{
		gout << "angle: " << howitzer.getElevation() << "degree\n";
	}
}