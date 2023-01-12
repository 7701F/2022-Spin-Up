/*
  Copyright (c) 2019-2023 7701F

  This software is provided 'as-is', without any express or implied warranty. In no event will
  the authors be held liable for any damages arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose, including commercial
  applications, and to alter it and redistribute it freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you wrote the
  original software. If you use this software in a product, an acknowledgment (see the following)
  in the product documentation is required.

  Portions Copyright (c) 2019-2023 7701F

  2. Altered source versions must be plainly marked as such, and must not be misrepresented as
  being the original software.

  3. This notice may not be removed or altered from any source distribution.
*/
#include "7701.h"

/* Util Functions */
namespace colors {
const int BLUE = 1;
const int RED = 2;
const int ERROR = 3;
} // namespace colors

/* Gets the # of Frisbees in the Indexer */
int getFrisbeesInIndexer() {
	int sensorDistance = distanceFilter.filter(indexerSensor.get());
	if (sensorDistance > 105) {
		return 0;
	} else if (sensorDistance > 90) {
		return 1;
	} else if (sensorDistance > 70) {
		return 2;
	} else {
		return 3;
	}
}

/* Get the color of the Roller from the Optical Sensor */
int getRollerColor() {
	if (rollerSensor.get_proximity() < 200) {
		return 0;
	}

	double hue = hueFilter.filter(rollerSensor.get_hue());
	if (hue < 260 && hue > 230) {
		return 1; // blue
	} else if (hue < 30 && hue > 0) {
		return 2; // red
	} else {
		return 3; // lol it doesnt know
	}
	return 0;
}

/* Set Roller to Red */
void setRollerRed() {
	int rollerStartTime = pros::millis();
	conveyor.move_velocity(100);
	while (getRollerColor() != 1 && pros::millis() - rollerStartTime < 1500) {
		pros::delay(10);
	}
	pros::delay(200);
	conveyor.move_velocity(0);
}

/* Set Roller to Blue */
void setRollerBlue() {
	int rollerStartTime = pros::millis();
	conveyor.move_velocity(100);
	while (getRollerColor() != 2 && pros::millis() - rollerStartTime < 1500) {
		pros::delay(10);
	}
	pros::delay(200);
	conveyor.move_velocity(0);
}

// fire disc from indexer
void fireDisc() {
	// extend piston to fire
	indexState = !indexState;
	indexer.set_value(indexState);

	// delay 125 ms then retract
	pros::delay(130);
	indexState = !indexState;
	indexer.set_value(indexState);
}

/* Programming Skills */
void Sauton() {
	// deFenestration::Flywheel::FwVelocitySet(96, 0.2);

	using namespace arms::chassis;
	arms::odom::reset({{0, 24}});

	turn({0, 24}, 75);
	move({{0, 24}}, 200);
}

/* Program an autonomous that moves to {{0, 0}} then turns to 90 degrees*/
void Pauton() {
	using namespace arms::chassis;
	arms::odom::reset({{20, 20}});

	turn({0, 0}, 90);
	move({{0, 0}}, 200);
}

/* longAuto */
void longAuto(int color, bool AWP) {
	using namespace arms::chassis;

	// reset odom to correct position
	arms::odom::reset({{-10, -65}}, 0);

	// move to the roller
	move({{10, -36}}, arms::THRU);
	move({{41, -65}});

	// set the roller to the correct color
	move(30, 200, arms::ASYNC);
	while (!settled()) {
		pros::delay(10);
	}

	// set the roller to the correct color
	conveyor.move_velocity(100);
	pros::delay(250);
	conveyor.move_velocity(0);

	// move back then turn
	move(-10, 100, arms::REVERSE);
	turn({53, 52}, 200);

	// check if AWP is enabled, else exit (return)
	if (!AWP) {
		return;
	}

	// set the flywheel to the correct speed, then wait for it to be up to speed
	deFenestration::Flywheel::FwVelocitySet(210, .92);
	while (current_error > 0.2) {
		pros::delay(10);
	}

	// fire piston and wait to ensure it is fired
	fireDisc();
	pros::delay(250);

	// spin down flywheel
	deFenestration::Flywheel::FwVelocitySet(0, 0);
}

/* shortAuto except it uses the arms::odom system for position */
void shortAuto(int color, bool AWP) {
	using namespace arms::chassis;

	// reset odom to correct position
	arms::odom::reset({{-60, 40}}, 270);

	// move to the roller
	move({{-60, -40}}, 200);
	move(30, 100, arms::ASYNC);
	while (!settled()) {
		pros::delay(10);
	}

	// set the roller to the correct color
	conveyor.move_velocity(100);
	pros::delay(250);
	conveyor.move_velocity(0);

	// move back then turn
	move(-10, 100, arms::REVERSE);
	// turn({-22.7196581703463, 21.439677428355}, 90);
	turn({53, 52}, 200);

	// check if AWP is enabled, else exit (return)
	if (!AWP) {
		return;
	}

	// set the flywheel to the correct speed, then wait for it to be up to speed
	deFenestration::Flywheel::FwVelocitySet(210, .92);
	while (current_error > 0.2) {
		pros::delay(10);
	}

	// fire piston and wait to ensure it is fired
	fireDisc();
	pros::delay(250);

	// spin down flywheel
	deFenestration::Flywheel::FwVelocitySet(0, 0);
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	// set brake to hold
	pbrake = true;
	prosBrake(1);
	pbrake = false;

	// reset odom
	arms::odom::reset({{0, 0}}, 0);

	/* Auton Selector Logic */
	// Negative = Blue
	// Positive = Red
	switch (arms::selector::auton) {
		case -5:
			// Do Nothing.
			break;
		case -4:
			longAuto(colors::BLUE, true);
			break;
		case -3:
			shortAuto(colors::BLUE, true);
			break;
		case -2:
			longAuto(colors::BLUE, false);
			break;
		case -1:
			shortAuto(colors::BLUE, false);
			break;
		case 0:
			break;
		case 1:
			shortAuto(colors::RED, false);
			break;
		case 2:
			longAuto(colors::RED, false);
			break;
		case 3:
			shortAuto(colors::RED, true);
			break;
		case 4:
			longAuto(colors::RED, true);
			break;
		case 5:
			// Do Nothing.
			break;
		default:
			throw printf("Invalid Auton: %d\n", arms::selector::auton);
			// break;
	}

	printf("Successfully ran auton: %d\n", arms::selector::auton);
}
