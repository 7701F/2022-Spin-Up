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
	conveyor.move_velocity(-500);
	while (getRollerColor() != 2 && pros::millis() - rollerStartTime < 800) {
		pros::delay(10);
	}
	conveyor.move_velocity(0);
	pros::delay(100);
}

/// @brief Set the roller to blue using the optical sensor
void setRollerBlue() {
	int rollerStartTime = pros::millis();
	conveyor.move_velocity(-500);
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
	pros::delay(5);
}

/// @brief  Fire a specified number of discs at a specified rpm
/// @param discs number of discs to fire
/// @param rpm rpm to fire discs at (will wait for flywheel to reach this speed for each disc)
void fireDiscs(int discs, int rpm) {
	float frpm = rpm;
	float predicted_drive = ((frpm / 210) + .02);

	// set the flywheel to the correct speed, then wait for it to be up to speed
	deFenestration::Flywheel::FwVelocitySet(rpm, predicted_drive);

	// loop through firing discs
	for (int i = 0; i < discs; i++) {
		while (current_error > 4) {
			pros::delay(30);
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

/// @brief Calibration auto
void calibrateAutos() {
	using namespace arms::chassis;

	prosBrake(true, 1);

	arms::odom::reset({{0, 0}}, 0);

	// move forward 5 inches
	move(45, 60, arms::RELATIVE);

	// turn right 90 degrees
	turn({0, 10}, 60, arms::RELATIVE);
}

/// @brief 90 pt theoretical Programming Skills Autonomous Routine
void Sauton() {
	using namespace arms::chassis;

	// set the brake
	prosBrake(true, 1);

	// reset odom to correct position
	arms::odom::reset({{0, 0}}, 180);

	// move 10 inches forward
	move(7, 100);
	setRollerRed(); // we're playing for the red alliance for roller's sake

	// move back then turn 90 degrees
	move(-19, 66, arms::REVERSE);
	turn(-90, 50, arms::RELATIVE);

	move(12, 50);

	move(7, 100);
	setRollerRed(); // we're playing for the red alliance for roller's sake

	move(-15.5, 80, arms::REVERSE);

	// turn -135 degrees, and halfway thru we fire two discs for 10 points
	turn({-147.6, 8.5}, 50);
	turn(192, 56, arms::RELATIVE); // turn 180 to face ur mom

	move(-30, 80, arms::REVERSE);
	fireDiscs(2, 135); // fire two discs, it's a free 10 points, will help in rankings
	move(30, 80);

	turn(180, 50, arms::RELATIVE);

	turn(-45, 50, arms::RELATIVE); // turn -45 to face the endgame firing position

	move(-9, 76, arms::REVERSE); // move 10 inches forward

	turn(172, 50, arms::RELATIVE);
	// toggleEndgame(); // fire endgame
}

/// @brief 174 pt theoretical Programming Skills Autonomous Routine
void Wauton() {
	using namespace arms::chassis;

	// set the brake
	prosBrake(true, 1);

	// reset odom to correct position
	arms::odom::reset({{0, 0}}, 270);

	deFenestration::Flywheel::FwVelocitySet(135, 0.65);

	// fire our preloaded discs
	for (int i = 0; i < 2; i++) {
		while (current_error > 3) {
			pros::delay(7);
		}

		// fire disc
		fireDisc();
	}

	// fire 6 more discs
	for (int i = 0; i < 7; i++) {
		while (current_error > 3) {
			pros::delay(7);
		}

		while (getDiscsInIndexer() < 1) {
			pros::delay(2);
		}

		// fire disc
		fireDisc();
	}

	deFenestration::Flywheel::FwVelocitySet(0, 0);

	move({-41, 10, 0}, 0);

	move(7, 67);
	setRollerRed();

	// move back then turn 90 degrees
	move(-19, 66, arms::REVERSE);
	turn(-90, 76, arms::RELATIVE);

	move(12, 50);

	move(7, 100);
	setRollerRed();

	arms::odom::reset({{0, 0}}, 180);

	move({-139.1, 102, 0}, 90);

	move(7, 100);
	setRollerRed();

	// move back then turn 90 degrees
	move(-19, 76, arms::REVERSE);
	turn(-90, 76, arms::RELATIVE);

	move(12, 80);

	move(7, 100);
	setRollerRed();

	move(-16, 80, arms::REVERSE);

	turn(90, 90, arms::RELATIVE); // turn -45 to face the endgame firing position

	move(9, 76, arms::REVERSE); // move 10 inches forward

	turn(-45, 50, arms::RELATIVE);
	// toggleEndgame(); // fire endgame
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
	fireDiscs(2, 185);
}

/// @brief Extra bit for Short Side AWP that goes to the row of discs and shoots 3 more discs
void shortAWP() {
	using namespace arms::chassis;

	// move to the row of discs
	turn(-45, 50, arms::RELATIVE);

	// turn on the intake
	conveyor.move_velocity(500);

	// move to the row of discs
	move(30, 100);

	// turn on the goal
	turn({-147.6, -8.5}, 50);

	// turn around so the flywheel is facing the goal
	turn(180, 80, arms::RELATIVE);
}

/// @brief Long Side Autonomous Routine, parameters are color and whether or not we're doing AWP
/// @param color Refer to COLOR enum
/// @param AWP Whether or not we're doing AWP (bool)
void longAuto(int color, bool AWP) {
	using namespace arms::chassis;

	// set the brake
	prosBrake(true, 1);

	// move to the roller
	move(-16.5, 100, arms::REVERSE);

	// turn
	turn(90, 50, arms::RELATIVE);

	// pre-spin up the roller
	conveyor.move_velocity(-470);

	// drive torwards the roller
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

	move(-10, 76, arms::REVERSE);
	// turn to the goal
	turn({-147.6, -8.5}, 50);

	// turn around so the flywheel is facing the goal
	turn(180, 25, arms::RELATIVE);

	// fire 2 discs
	fireDiscs(2, 185);

	// check if AWP is enabled, else exit (return)
	if (!AWP) {
		longAWP();
		return;
	} else {
		return;
	}
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

	// turn to the goal
	turn({-147.6, -8.5}, 100);

	// turn around
	turn(198, 50, arms::RELATIVE);
	// fire 2 discs
	toggleAngler();
	fireDiscs(2, 190);
	toggleAngler();

	// check if AWP is enabled, else exit (return)
	if (!AWP) {
		shortAWP();
		return;
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
