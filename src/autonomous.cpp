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

namespace colors {
const int BLUE = 1;
const int RED = 2;
const int ERROR = 3;
} // namespace colors

void setRollerRed(){
    int rollerStartTime = pros::millis();
    conveyor.move_velocity(100);
    while(getRollerColor() != 2 && pros::millis() - rollerStartTime < 1500){
        pros::delay(10);
    }
    conveyor.move_velocity(0);
    pros::delay(50);
    rollerStartTime = pros::millis();
    conveyor.move_velocity(100);
    while(getRollerColor() != 1 && pros::millis() - rollerStartTime < 1500){
        pros::delay(10);
    }
    conveyor.move_velocity(50);
    pros::delay(250);
    conveyor.move_velocity(0);
}

void setRollerBlue(){
    int rollerStartTime = pros::millis();
    conveyor.move_velocity(100);
    while(getRollerColor() != 1 && pros::millis() - rollerStartTime < 1500){
        pros::delay(10);
    }
    conveyor.move_velocity(0);
    pros::delay(50);
    rollerStartTime = pros::millis();
    conveyor.move_velocity(100);
    while(getRollerColor() != 2 && pros::millis() - rollerStartTime < 1500){
        pros::delay(10);
    }
    conveyor.move_velocity(50);
    pros::delay(250);
    conveyor.move_velocity(0);
}

// fire disc from indexer
void fireDisc() {
	// extend piston to fire
	indexState = !indexState;
	indexer.set_value(indexState);

	// wait for piston to fire, then retract 150ms later
	pros::delay(150);
	indexState = !indexState;
	indexer.set_value(indexState);
}

// fire disc(s) from indexer
void fireDiscs(int discs) {
	// set the flywheel to the correct speed, then wait for it to be up to speed
	deFenestration::Flywheel::FwVelocitySet(170, .92);

	// loop through firing discs
	for (int i = 0; i < discs; i++) {
		while (current_error > 10) {
			pros::delay(10);
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
}

/* Autonomous Functions */

// calibrate robot distance for movement
void calibrateAutos() {
	using namespace arms::chassis;

	prosBrake(false);

	arms::odom::reset({{0, 0}}, 0);

	// move forward 5 inches
	move(5, 60, arms::RELATIVE);

	// turn right 90 degrees
	// turn({0, 10}, 60, arms::RELATIVE);
}

/* Programming Skills */
/* Wauton */
void Wauton() {
	using namespace arms::chassis;

	// reset odom to correct position
	arms::odom::reset({{0, 0}}, 0);

	// move to the roller
	move({10, -10, 90}, 100);

	// set the roller to the correct color
	setRollerRed();

	// move back then turn
	move({-10, 10, 180}, 100, arms::REVERSE);
}

/* longAuto that drives forward 16.5 inches, sets our position to 0,0 (0), turns 90
 * degrees relitive to current position, then turns around, drives forward 16.5 inches
 */
void longAuto(int color, bool AWP) {
	using namespace arms::chassis;

	// reset odom to correct position
	arms::odom::reset({{0, 0}}, 0);

	// move to the roller
	move(16.5, 100);

	// turn right 90 degrees
	turn(90, 25, arms::RELATIVE);

	// move back then turn
	move(-10, 100, arms::REVERSE);

	// turn around
	turn(90, 25, arms::RELATIVE);

	// drive torwards the roller
	move(24, 100);

	// set the roller to the correct color
	// conveyor.move_velocity(100);
	// pros::delay(500);
	// conveyor.move_velocity(0);
	// switch statement on color
	switch (color) {
		case 1:
			setRollerRed();
			break;
		case 2:
			setRollerBlue();
			break;
		default:
			break;
	}

	// wait 250 just to be safe
	pros::delay(250);

	// drive backwards
	move(-10, 100, arms::REVERSE);

	// turn to the goal
	turn({-147.6, -8.5}, 50);

	// turn around so the flywheel is facing the goal
	turn(180, 25, arms::RELATIVE);

	// check if AWP is enabled, else exit (return)
	if (!AWP) {
		return;
	}

	// fire 2 discs
	fireDiscs(2);
}

/* shortAuto except it uses the arms::odom system for position */
void shortAuto(int color, bool AWP) {
	using namespace arms::chassis;

	// reset odom to correct position
	arms::odom::reset({{-0, 0}}, 0);

	// set our intake on
	conveyor.move_velocity(450);

	// move to the roller
	// drives forward 30 inches at 100% speed
	move(30, 76, arms::ASYNC | arms::RELATIVE);

	// set the roller to the correct color
	// currently time based, will be changed to optical sensor based soon™
	// conveyor.move_velocity(-100);
	// pros::delay(500);
	// conveyor.move_velocity(0);

	// return;

	// switch statement on color
	switch (color) {
		case 1:
			setRollerRed();
			break;
		case 2:
			setRollerBlue();
			break;
		default:
			break;
	}

	return;

	// move back then turn
	move(-10, 100, arms::REVERSE | arms::RELATIVE);

	// turn to the goal
	turn({-147.6, -8.5}, 100);

	// turn around
	turn(180, 25, arms::RELATIVE);

	// check if AWP is enabled, else exit (return)
	if (!AWP) {
		return;
	}

	// fire 2 discs
	fireDiscs(2);
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
	prosBrake(true, 1);

	// reset odom
	arms::odom::reset({{0, 0}}, 0);

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
			calibrateAutos();
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
