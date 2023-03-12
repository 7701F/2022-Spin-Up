/*
  Copyright (c) 2019-2023 7701F

  This software is provided 'as-is', without any express or implied warranty. In no event
  will the authors be held liable for any damages arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose, including
  commercial applications, and to alter it and redistribute it freely, subject to the
  following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you
  wrote the original software. If you use this software in a product, an acknowledgment
  (see the following) in the product documentation is required.

  Portions Copyright (c) 2019-2023 7701F

  2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original software.

  3. This notice may not be removed or altered from any source distribution.
*/
#include "7701.hpp"

// handy macros for colors so we don't have to remember what color is what number
namespace colors {
const int BLUE = 1;
const int RED = 2;
const int ERROR = 3;
} // namespace colors

// set roller to red
void setRollerRed() {
	int rollerStartTime = pros::millis();
	conveyor.move_velocity(-500);
	while (getRollerColor() != 2 && pros::millis() - rollerStartTime < 800) {
		pros::delay(10);
	}
	conveyor.move_velocity(0);
	pros::delay(300);
}

// set roller to blue
void setRollerBlue() {
	int rollerStartTime = pros::millis();
	conveyor.move_velocity(-500);
	while (getRollerColor() != 1 && pros::millis() - rollerStartTime < 800) {
		pros::delay(10);
	}
	conveyor.move_velocity(0);
}

// fire disc from indexer
void fireDisc() {
	// extend piston to fire
	indexState = !indexState;
	indexer.set_value(indexState);

	// wait for piston to fire, then retract.
	pros::delay(150);
	indexState = !indexState;
	indexer.set_value(indexState);
	pros::delay(21);
}

// fire disc(s) from indexer
void fireDiscs(int discs, int rpm) {
	// set the flywheel to the correct speed, then wait for it to be up to speed
	deFenestration::Flywheel::FwVelocitySet(rpm, .81);

	// loop through firing discs
	for (int i = 0; i < discs; i++) {
		while (current_error > 3) {
			pros::delay(30);
		}

		// fire piston and wait to ensure it is fired
		fireDisc();
		pros::delay(125);
	}

	// spin down flywheel
	deFenestration::Flywheel::FwVelocitySet(0, 0);
}

// function for toggling the endgame
void toggleEndgame() {
	endgameState = !endgameState;
	endgame.set_value(endgameState);
	endgame2.set_value(endgameState);
}

/* Autonomous Functions */

// calibrate robot distance for movement
void calibrateAutos() {
	using namespace arms::chassis;

	prosBrake(true, 1);

	arms::odom::reset({{0, 0}}, 0);

	// move forward 5 inches
	// move(5, 60, arms::RELATIVE);

	// turn right 90 degrees
	// turn({0, 10}, 60, arms::RELATIVE);
}

/* Programming Skills */
/* Wauton */
void Wauton() {
	using namespace arms::chassis;

	// set the brake
	prosBrake(true, 1);

	// reset odom to correct position
	arms::odom::reset({{0, 0}}, 180);

	// move 10 inches forward
	move(7, 57);

	setRollerRed(); // we're playing for the red alliance for roller's sake
	// conveyor.move_velocity(0);

	// move back then turn 90 degrees
	move(-19, 66, arms::REVERSE);
	turn(-90, 45, arms::RELATIVE);

	move(18.89, 50); // move forward 24 inches
	setRollerRed();  // we're playing for the red alliance for roller's sake

	// move 20 inches back
	move(-15.5, 40, arms::REVERSE);

	// turn -135 degrees, and halfway thru we fire two discs for 10 points

	// first, turn -90 to face the goal
	turn({-147.6, 8.5}, 50);
	turn(192, 56, arms::RELATIVE); // turn 180 to face ur mom
	// turn(90, 43, arms::RELATIVE);

	move(-30, 50, arms::REVERSE);
	fireDiscs(2, 135); // fire two discs, it's a free 10 points, will help in rankings why
	                   // you say disccs in the fire discs methodz
	move(30, 50, arms::RELATIVE);

	// turn 180
	turn(180, 50, arms::RELATIVE);

	turn(-45, 43, arms::RELATIVE); // turn -45 to face the endgame firing position

	move(-9, 76, arms::REVERSE); // move 10 inches forward

	turn(172, 50, arms::RELATIVE);
	toggleEndgame(); // fire endgame
}

/* far side auton */
void longAuto(int color, bool AWP) {
	using namespace arms::chassis;

	// set the brake
	prosBrake(true, 1);

	// move to the roller
	move(-16.5, 76, arms::REVERSE);

	// turn
	turn(90, 50, arms::RELATIVE);

	// pre-spin up the roller
	conveyor.move_velocity(-470);

	// drive torwards the roller
	move(24, 76);

	// set the roller to the correct color
	// conveyor.move_velocity(100);
	// pros::delay(500);
	// conveyor.move_velocity(0);
	// switch statement on color
	switch (color) {
		case 1:
			setRollerBlue();
			break;
		case 2:
			setRollerRed();
			break;
		default:
			break;
	}

	// reset odom to correct position
	arms::odom::reset({{0, 0}}, 0);

	// wait 250 just to be safe
	pros::delay(250);

	// drive forward 10 inches
	move(10, 76);

	// turn to the goal
	turn({-147.6, -8.5}, 50);

	// turn around so the flywheel is facing the goal
	turn(180, 25, arms::RELATIVE);

	// check if AWP is enabled, else exit (return)
	if (!AWP) {
		return;
	}

	// fire 2 discs
	fireDiscs(2, 170);
}

/* close side auton */
void shortAuto(int color, bool AWP) {
	using namespace arms::chassis;

	// set the brake
	prosBrake(true, 1);

	// reset odom to correct position
	arms::odom::reset({{0, 0}}, 180);

	// set our intake on
	conveyor.move_velocity(-470);

	// move to the roller
	// drives forward 30 inches at 100% speed
	move(6, 57);

	// switch statement on color
	switch (color) {
		case 1:
			setRollerBlue();
			break;
		case 2:
			setRollerRed();
			break;
		default:
			break;
	}

	// move back then turn
	move(-6, 100, arms::REVERSE);

	// check if AWP is enabled, else exit (return)
	if (!AWP) {
		return;
	}

	// turn to the goal
	turn({-147.6, -8.5}, 100);

	// turn around
	turn(198, 50, arms::RELATIVE);
	// fire 2 discs
	fireDiscs(2, 190);
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
	printf("Running auton: %d\n", arms::selector::auton);

	/* Auton Selector Logic */
	// Negative = Blue
	// Positive = Red
	switch (arms::selector::auton) {
		case -5: // Do Nothing.
			printf("Do Nothing\n");
			break;
		case -4: // Blue Long AWP
			longAuto(colors::BLUE, true);
			break;
		case -3: // Blue Short AWP
			shortAuto(colors::BLUE, true);
			break;
		case -2: // Blue Long
			longAuto(colors::BLUE, false);
			break;
		case -1: // Blue Short
			shortAuto(colors::BLUE, false);
			break;
		case 0: // Programming Skills
			Wauton();
			break;
		case 1: // Red Short
			shortAuto(colors::RED, false);
			break;
		case 2: // Red Long
			longAuto(colors::RED, false);
			break;
		case 3: // Red Short AWP
			shortAuto(colors::RED, true);
			break;
		case 4: // Red Long AWP
			longAuto(colors::RED, true);
			break;
		case 5: // Do Nothing.
			printf("Do Nothing\n");
			break;
		default:
			throw printf("Invalid Auton: %d\n", arms::selector::auton);
			// break;
	}
}
