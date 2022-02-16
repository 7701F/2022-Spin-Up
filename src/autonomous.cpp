/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "main.h"

std::int32_t mmToInch() {
	return (distanceR.get() / 25.4) + 3;
}

// Right win point
void Rauton() {
	arms::chassis::move(20, 80);
	arms::claw::toggleClaw();
	liftMotors.moveRelative(30, 100);
	pros::delay(300);
	arms::chassis::turnAsync(-60, 80);
	arms::chassis::move(-20, 80);
	arms::claw::toggleClaw();
	pros::delay(30);
}

// Yellow goal
void Yauton() {
	arms::chassis::move(64, 80);
	arms::claw::toggleClaw();
	pros::delay(200);
	arms::chassis::move(-50, 100);
	arms::claw::toggleClaw();
}

// Left win point
void Lauton() {
	arms::claw::puncher();
	arms::chassis::turn(90, 80);
	arms::chassis::move(5, 50);
	arms::claw::toggleClaw();
	arms::chassis::move(-15, 80);
	pros::delay(500);
	arms::chassis::move(-6, 80);
	arms::chassis::turn(-80, 60);
	arms::chassis::move(60, 100);
	arms::chassis::moveAsync(5, 75);
	arms::claw::toggleClaw();
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
	arms::claw::toggleClaw();
	pros::delay(850);
	arms::chassis::move(-80, 80);
	arms::chassis::turn(45, 50);
	arms::claw::toggleClaw();
	pros::delay(300);
	arms::chassis::turn(-85, 50);
	arms::chassis::move(65, 80);
	arms::chassis::move(50, 80);
}

// Programming Skills 2.0
void Sauton2() {
	// Fetch blue start MOGO
	arms::chassis::move(8, 50);
	// arms::chassis::turnAbsolute(180, 50);
	// winchM.move_relative(-2065, -100);
	// pros::delay(3250);
	// arms::chassis::move(dist * -1, 50);
	// winchM.move_relative(1100, 100);
	// pros::delay(1400);
	arms::chassis::move(70, 80);
	// Move forward to turn
	arms::chassis::move(-25, 50);
	arms::chassis::turn(-90, 50);
	// Turn to face yellow right MOGO
	arms::chassis::move(25, 100);
	// Grab yellow right MOGO
	arms::claw::toggleClaw();
	arms::chassis::turn(90, 50);
	arms::chassis::move(15, 80);
	arms::chassis::turn(-90, 50);
	liftMotors.moveRelative(380, 100);
	arms::chassis::move(10, 80);
	arms::chassis::turnAbsolute(0);
	arms::chassis::move(10);
	// Place yellow MOGO on balance board
	arms::claw::toggleClaw();
	// Move back to face yellow middle MOGO
	arms::chassis::move(-10, 10);
	arms::chassis::turnAsync(180, 50);
	liftMotors.moveRelative(-380, -100);
	arms::lift::waitUntilSettled();
	arms::chassis::move(50, 50);
	// Grab yellow middle MOGO
	arms::claw::toggleClaw();
	// Turn around to face the balance board
	arms::chassis::move(4, 50);
	arms::chassis::turnAbsolute(0, 50);
	arms::chassis::moveAsync(60, 80);
	liftMotors.moveRelative(380, 80);
	arms::lift::waitUntilSettled();
	arms::chassis::move(10, 50);
	// Drop the mogo and move back to face the balance board
	arms::claw::toggleClaw();
	// Move back to face the yellow left MOGO
	arms::chassis::move(-10, 50);
	arms::chassis::turn(-180, 50);
	arms::chassis::move(20, 80);
	liftMotors.moveRelative(-380, -80);
	arms::lift::waitUntilSettled();
	arms::chassis::move(10, 50);
	liftMotors.moveAbsolute(3, -80);
	arms::lift::waitUntilSettled();
	arms::chassis::move(30, 80);
	arms::chassis::turnAbsolute(90, 50);
	// Grab the yellow left MOGO
	arms::claw::toggleClaw();
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
	arms::claw::toggleClaw();
	// Move back
	arms::chassis::move(-30, 80);
	liftMotors.moveAbsolute(3, 80);
	arms::lift::waitUntilSettled();
	// Turn to face the red MOGO
	arms::chassis::turnAbsolute(-90, 50);
	// vision::redLocate();
	arms::chassis::move(10, 80);
	arms::chassis::turnAbsolute(-30, 50);
	arms::chassis::move(50, 80);
	// Grab it
	arms::claw::toggleClaw();
	arms::chassis::move(-10, 50);
	arms::chassis::turnAbsolute(-15, 50);
	// Move it to the red side
	arms::chassis::move(50, 80);
	// Drop it
	arms::claw::toggleClaw();
	// Move back to our side
	arms::chassis::move(-70, 100);
}

// Programming Skills 3.0
void Sauton3() {
	arms::odom::init();
	arms::odom::reset();
	arms::chassis::resetAngle(180);
	winchM.move_relative(-2065, -100);
	pros::delay(3250);
	arms::chassis::move(-78, 50);
	winchM.move_relative(1100, 100);
	pros::delay(1400);
	arms::chassis::turn(90, 50);
	ringM.move_velocity(600);
	arms::chassis::move(50);
	ringM.move_velocity(0);
	arms::chassis::move(30);
	arms::claw::toggleClaw();
	arms::chassis::turn(-90);
	arms::chassis::move(96);
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

	// Auton Selector Logic
	switch (arms::selector::auton) {
		case -4:
			break;
		case -3:
			break;
		case -2:
			break;
		case -1:
			arms::chassis::move(65, 80);
			arms::chassis::moveAsync(10);
			arms::claw::toggleClaw();
			pros::delay(200);
			arms::chassis::move(-50, 100);
			break;
		case 0:
			Sauton3();
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
			break;
		default:
			break;
	}

	printf("Successfully ran auton: %d\n", arms::selector::auton);
}
