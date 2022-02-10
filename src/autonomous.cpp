/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <array>

#include "autonfunctions.hpp"
#include "main.h"
#include "opcontrol.h"

// Right win point
void Rauton() {
	arms::chassis::move(20, 80);
	clawM.move_relative(200, 100);
	pros::delay(300);
	liftMotors.moveRelative(30, 100);
	pros::delay(300);
	arms::chassis::move(-20, 80);
	arms::chassis::turn(-60, 80);
}

// Yellow goal
void Yauton() {
	arms::chassis::move(54, 100);
	clawM.move_relative(200, 100);
	pros::delay(300);
	arms::chassis::move(-55, 100);
}

// Left win point
void Lauton() {
	arms::chassis::move(5, 50);
	clawM.move_relative(170, 100);
	pros::delay(300);
	clawM.move_relative(40, 100);
	arms::chassis::move(-15, 80);
	pros::delay(500);
	clawM.move_relative(-170, -50);
	pros::delay(300);
	arms::chassis::move(-6, 80);
	arms::chassis::turn(-80, 60);
	arms::chassis::move(60, 100);
	arms::chassis::moveAsync(5, 75);
	clawM.move_relative(210, 100);
	pros::delay(300);
	liftMotors.moveRelative(30, 75);
	pros::delay(500);
	arms::chassis::move(-60, 100);
}

// Programming Skills
void Sauton() {
	winchM.move_relative(-2065, -100);
	pros::delay(3250);
	arms::chassis::move(-30, 50);
	winchM.move_relative(1100, 100);
	pros::delay(1250);
	arms::chassis::move(28, 60);
	arms::chassis::turn(150, 50);
	arms::chassis::move(80, 80);
	clawM.move_relative(210, 50);
	pros::delay(850);
	arms::chassis::move(-80, 80);
	arms::chassis::turn(45, 50);
	clawM.move_relative(-210, 50);
	pros::delay(300);
	arms::chassis::turn(-85, 50);
	arms::chassis::move(65, 80);
	arms::chassis::move(50, 80);
}

/*
  arms::chassis::resetAngle();
  while (arms::chassis::imu->get_rotation() != 0) {
    if (arms::chassis::imu->get_rotation() > 0) {
      arms::chassis::turn(-1, 50);
    } else {
      arms::chassis::turn(1, 50);
    }
  }
*/

// Programming Skills 2.0
void Sauton2() {
	// Fetch blue start MOGO
	winchM.move_relative(-2065, -100);
	pros::delay(3250);
	arms::chassis::move(-28, 50);
	winchM.move_relative(1100, 100);
	pros::delay(1400);
	// Move forward to turn
	arms::chassis::move(30, 50);
	arms::chassis::turnAbsolute(45, 50);
	arms::chassis::move(7, 80);
	// Turn to face yellow right MOGO
	arms::chassis::turnAbsolute(90, 50);
	arms::chassis::move(90, 100);
	// Grab yellow right MOGO
	clawM.move_relative(210, 50);
	arms::claw::waitUntilSettled();
	arms::chassis::turnAbsolute(-90, 50);
	arms::chassis::move(15, 80);
	arms::chassis::turnAbsolute(90, 50);
	liftMotors.moveRelative(380, 100);
	arms::chassis::move(10, 80);
	// Place yellow MOGO on balance board
	clawM.move_relative(-210, -50);
	arms::claw::waitUntilSettled();
	// Move back to face yellow middle MOGO
	arms::chassis::move(-10, 10);
	arms::chassis::turnAbsoluteAsync(180, 50);
	liftMotors.moveRelative(-380, -100);
	arms::lift::waitUntilSettled();
	arms::chassis::move(50, 50);
	// Grab yellow middle MOGO
	clawM.move_relative(210, 80);
	arms::claw::waitUntilSettled();
	// Turn around to face the balance board
	arms::chassis::move(4, 50);
	arms::chassis::turnAbsolute(180, 50);
	arms::chassis::moveAsync(60, 80);
	liftMotors.moveRelative(380, 80);
	arms::lift::waitUntilSettled();
	arms::chassis::move(10, 50);
	// Drop the mogo and move back to face the balance board
	clawM.move_relative(-210, -80);
	arms::claw::waitUntilSettled();
	// Move back to face the yellow left MOGO
	arms::chassis::move(-10, 50);
	arms::chassis::turnAbsolute(-180, 50);
	arms::chassis::move(20, 80);
	liftMotors.moveRelative(-380, -80);
	arms::lift::waitUntilSettled();
	arms::chassis::move(10, 50);
	liftMotors.moveAbsolute(3, -80);
	arms::lift::waitUntilSettled();
	arms::chassis::move(30, 80);
	arms::chassis::turnAbsolute(90, 50);
	// Grab the yellow left MOGO
	clawM.move_relative(210, 80);
	arms::claw::waitUntilSettled();
	// Turn torwards the balance board
	arms::chassis::turnAbsolute(90, 50);
	// Drive to it
	arms::chassis::move(30, 80);
	// Get to the right spot on the balance board
	arms::chassis::turnAbsolute(90, 80);
	arms::chassis::move(20, 80);
	arms::chassis::turnAbsolute(-90, 80);
	// Put up lift
	liftMotors.moveRelative(380, 80);
	arms::lift::waitUntilSettled();
	arms::chassis::move(10, 50);
	// Drop the MOGO
	clawM.move_relative(-210, -80);
	arms::claw::waitUntilSettled();
	// Move back
	arms::chassis::move(-30, 80);
	liftMotors.moveAbsolute(3, 80);
	arms::lift::waitUntilSettled();
	// Turn to face the red MOGO
	arms::chassis::turnAbsolute(-90, 50);
	pros::delay(70);
	arms::chassis::turnAbsolute(-30, 50);
	arms::chassis::move(50, 80);
	// Grab it
	clawM.move_relative(210, 80);
	arms::claw::waitUntilSettled();
	arms::chassis::move(-10, 50);
	arms::chassis::turnAbsolute(-15, 50);
	// Move it to the red side
	arms::chassis::move(50, 80);
	// Drop it
	clawM.move_relative(-210, -80);
	arms::claw::waitUntilSettled();
	// Move back to our side
	arms::chassis::move(-70, 100);
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
	arms::chassis::resetAngle();
	arms::pid::init();
	// killTask();

	// Auton Selector Logic
	switch (arms::selector::auton) {
	case -4:
		arms::odom::init();
		arms::odom::reset({0, 0}, 0);

		arms::odom::move({10, 0});
		// arms::chassis::arcRight(1000, 1, 50, 1);
		// arms::chassis::arcLeft(1800, 1, 50, 2);
		// arms::chassis::arcRight(1600, 1, 50, 3);
		break;
	case -3:

		break;
	case -2:

		break;
	case -1:

		break;
	case 0:
		Sauton2();
		break;
	case 1:
		Yauton();
		break;
	case 2:
		Rauton();
		break;
	case 3:
		Lauton();
		break;
	case 4:
		// arms::odom::reset();
		// arms::odom::move({1, 1});
		break;
	default:
		break;
	}

	printf("Successfully ran auton: %d\n", arms::selector::auton);

	while (true) {
		pros::delay(1000);
	}
}
