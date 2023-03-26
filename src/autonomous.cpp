/*
  Copyright (c) 2019-2023 7701F

  This software is provided 'as-is', without any express or implied warranty. In no event
  will the authors be held liable for any damages arising from the use of this software.
*/
#include "7701.hpp"

namespace colors {
/// @brief Blue
const int BLUE = 1;
/// @brief Red
const int RED = 2;
/// @brief Error (no color detected)
const int ERROR = 3;
} // namespace colors

/// @brief Set the roller to red using the optical sensor
void setRollerRed() {
	int rollerStartTime = pros::millis();
	conveyor.move_velocity(-600);
	while (getRollerColor() != 2 && pros::millis() - rollerStartTime < 800) {
		pros::delay(10);
	}
	conveyor.move_velocity(0);
	pros::delay(100);
}

/// @brief Set the roller to blue using the optical sensor
void setRollerBlue() {
	int rollerStartTime = pros::millis();
	conveyor.move_velocity(-600);
	while (getRollerColor() != 1 && pros::millis() - rollerStartTime < 800) {
		pros::delay(10);
	}
	conveyor.move_velocity(0);
	pros::delay(100);
}

/// @brief Fire a single disc from the indexer
void fireDisc() {
	// extend piston to fire
	indexState = !indexState;
	indexer.set_value(indexState);

	// wait for piston to fire, then retract.
	pros::delay(135);
	indexState = !indexState;
	indexer.set_value(indexState);
	pros::delay(20);
}

/// @brief  Fire a specified number of discs at a specified rpm
/// @param discs number of discs to fire
/// @param rpm rpm to fire discs at (will wait for flywheel to reach this speed for each disc)
void fireDiscs(int discs, int rpm, float predicted_drive) {
	// set the flywheel to the correct speed, then wait for it to be up to speed
	deFenestration::Flywheel::FwVelocitySet(rpm, predicted_drive);

	// loop through firing discs
	for (int i = 0; i < discs; i++) {
		while (current_error > 5) {
			pros::delay(100);
		}

		// fire piston and wait to ensure it is fired
		fireDisc();
		pros::delay(150);
	}

	// spin down flywheel
	deFenestration::Flywheel::FwVelocitySet(0, 0);
}

/// @brief Fires the endgame pistons, deploying our 7 string shooter
void toggleEndgame() {
	endgameState = !endgameState;
	endgame.set_value(endgameState);
	endgame2.set_value(endgameState);
}

/// @brief toggle angler
void toggleAngler() {
	aState = !aState;
	angler.set_value(aState);
}

/// @brief 90 pt theoretical Programming Skills Autonomous Routine
void Sauton() {
	using namespace arms::chassis;

	// set the brake
	prosBrake(true, 1);

	// reset odom to correct position
	arms::odom::reset({{0, 0}}, 180);

	conveyor.move_velocity(-500);

	// move 10 inches forward
	move(7, 30);
	setRollerRed(); // we're playing for the red alliance for roller's sake

	// move back then turn 90 degrees
	move(-19, 66, arms::REVERSE);
	turn(-90, 50, arms::RELATIVE);

	move(12, 50);

	move(7, 76);
	setRollerRed(); // we're playing for the red alliance for roller's sake

	move(-15.5, 80, arms::REVERSE);

	// turn -135 degrees, and halfway thru we fire two discs for 10 points
	turn({-147.6, 8.5}, 50);
	turn(192, 56, arms::RELATIVE); // turn 180 to face ur mom

	move(-30, 80, arms::REVERSE);
	fireDiscs(2, 135, .86); // fire two discs, it's a free 10 points, will help in rankings
	move(30, 80);

	turn(180, 50, arms::RELATIVE);

	turn(-45, 50, arms::RELATIVE); // turn -45 to face the endgame firing position

	move(-9, 76, arms::REVERSE); // move 10 inches forward

	turn(172, 50, arms::RELATIVE);
	// toggleEndgame(); // fire endgame
}

void Wauton() {
	using namespace arms::chassis;

	// Red Goal: 6.52, -44.06
	// Blue Goal: 95.38, 39.17

	// reset odom to correct position
	arms::odom::reset({0, 0}, 107);

	prosBrake(false);

	deFenestration::Flywheel::FwVelocitySet(136, 0.65);

	// timeout in case we don't hit the target speed, utilzing a pros::millis() timer. also has an exit check
	int startTime = pros::millis();
	bool exit = false;
	int disks;
	bool discIn = false;
	while (pros::millis() - startTime < 5000 && exit == false) {
		// fire our preloaded discs
		for (int i = 1; i < 3; i++) {
			while (current_error > 4) {
				pros::delay(100);
			}
			pros::delay(200);
			disks = getDiscsInIndexer();

			while (getDiscsInIndexer() == 0 && discIn == false) {
				pros::delay(75);
				if (getDiscsInIndexer() > 0) {
					discIn = true;
				}
				pros::delay(30);
			}
			pros::delay(200);
			disks = getDiscsInIndexer();

			// fire disc
			fireDisc();
			discIn = false;
			while (getDiscsInIndexer() > disks) {
				pros::delay(30);
			}
			pros::delay(100);
		}
		exit = true;
	}
	pros::delay(200);
	conveyor.move_velocity(600);

	// another timeout in case we don't detect a disc, utilzing a pros::millis() timer. also has an exit check
	startTime = pros::millis();
	exit = false;
	discIn = false;
	while (pros::millis() - startTime < 10000 && exit == false) {
		// fire 7 more discs
		for (int i = 0; i < 7; i++) {
			while (current_error > 4) {
				pros::delay(100);
			}

			while (getDiscsInIndexer() == 0 && discIn == false) {
				pros::delay(75);
				if (getDiscsInIndexer() > 0) {
					discIn = true;
				}
				pros::delay(30);
			}
			pros::delay(200);
			disks = getDiscsInIndexer();

			// fire disc
			fireDisc();
			discIn = false;
			while (getDiscsInIndexer() < disks) {
				pros::delay(30);
			}
			pros::delay(275);
		}

		exit = true;
	}
	conveyor.move_velocity(0);

	turn(60, 76);
	move(30, 76);

	move({22, 33.25}, 76);
	turn(125);
	move(15);
	move({19, 34.5}, 76, arms::REVERSE);
	turn(180, 50);

	move(19, 50);
	move(7, 30);
	setRollerRed();

	// move back then turn 90 degrees
	move(-18.6, arms::REVERSE);
	turn(90, 76);

	move(19, 50);
	move(7, 30);
	setRollerRed();

	move(-18.6, arms::REVERSE);
	turn(270);

	// move back to position to move to the other corner
	move({6, 0, 270}, 76);

	move({6, -46.6}, 76);
	// move({4, -52.6, 0}, 76);
	move({16, -46.6}, 76);
	move({26, -46.6}, 76);
	turn(0, 50);

	// move to the other corner
	move({90, -34.4}, 80);
	turn(56);
	move(7);
	move(-7, arms::REVERSE);

	turn(0);

	move(19, 50);
	move(7, 30);
	setRollerRed();

	move(-18.6, arms::REVERSE);
	turn(270, 76);

	move(19, 50);
	move(7, 30);
	setRollerRed();
	move(-16, 80, arms::REVERSE);

	turn(0, 50);
	turn(-45, 50, arms::RELATIVE);
	move(11, 10);
	toggleEndgame(); // fire endgame
	turn(270, 26);
	// move(7.5, 10);
}

/// @brief Extra bit for Long Side AWP that goes to the row of discs and shoots 3 more discs
void longAWP() {
	using namespace arms::chassis;

	turn(-45, 50, arms::RELATIVE);
	turn(-90, 50, arms::RELATIVE);

	// move to the row of discs
	move(30, 100);

	// turn on the intake
	conveyor.move_velocity(500);

	// move to the row of discs
	move(30, 100);

	// turn on the goal
	turn({-147.6, -8.5}, 50);

	// turn around so the flywheel is facing the goal
	turn(180, 25, arms::RELATIVE);

	// fire 2 discs
	fireDiscs(2, 185, .86);
}

/// @brief Extra bit for Short Side AWP that goes to the row of discs and shoots 3 more discs
void shortAWP() {
	using namespace arms::chassis;

	deFenestration::Flywheel::FwVelocitySet(187, .86);

	// turn to the goal
	turn({-147.6, -8.5}, 70);
	turn(185, 70, arms::RELATIVE);

	fireDiscs(2, 187, .96);

	return;

	// move to the row of discs
	turn(180, 80, arms::RELATIVE);
	turn(-45, 80, arms::RELATIVE);

	// turn on the intake
	conveyor.move_velocity(500);

	// move to the row of discs
	move(30, 100);

	// turn on the goal & turn off the intake
	conveyor.move_velocity(0);
	turn({-147.6, -8.5}, 50);

	// turn around so the flywheel is facing the goal
	turn(198, 60, arms::RELATIVE);
	fireDiscs(2, 185, .86);
}

/// @brief Long Side Autonomous Routine, parameters are color and whether or not we're doing AWP
/// @param color Refer to COLOR enum
/// @param AWP Whether or not we're doing AWP (bool)
void longAuto(int color, bool AWP) {
	using namespace arms::chassis;

	// set the brake
	prosBrake(true, 1);

	// reset odom to correct position
	arms::odom::reset({{7, 0}}, 270);

	// move to the roller
	move({7, -20}, 76);
	// move({4, -24}, 76);

	// pre-spin up the roller
	conveyor.move_velocity(-470);

	// drive torwards the roller
	turn(180);
	move(7, 76);
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
	arms::odom::reset({{0, 0}}, 180);

	if (!AWP)
		return;

	move(-5, 76, arms::REVERSE);
	// turn to the goal
	turn({-147.6, -8.5}, 50);

	// turn around so the flywheel is facing the goal
	turn(173, 76, arms::RELATIVE);

	// fire 2 discs
	fireDiscs(2, 200, .86);

	// check if AWP is enabled, else exit (return)
	// longAWP();
	// return;
	// } else {
	// return;
	// }
}

/// @brief Short Side Autonomous Routine, parameters are color and whether or not we're doing AWP
/// @param color Refer to COLOR enum
/// @param AWP Whether or not we're doing AWP (bool)
void shortAuto(int color, bool AWP) {
	using namespace arms::chassis;

	// set the brake
	prosBrake(true, 1);

	// reset odom to correct position
	arms::odom::reset({{0, 0}}, 180);

	// set our intake on
	conveyor.move_velocity(-470);

	// move to the roller
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
	if (AWP) {
		shortAWP();
	} else {
		return;
	}
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
