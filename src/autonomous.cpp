/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "ARMS/pid.h"
#include "main.h"

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

/*
// Drive forward AND grab and pull tower auton
void game_autonomous()
{
	leftMtr.move_relative(300, 75);
	leftMtrR.move_relative(300, 75);
	rightMtr.move_relative(300, 75);
	rightMtrR.move_relative(300, 75);
	pros::delay(300);
	clawM.move_relative(1200, 50);
	rightLift.move_relative(30, 100);
	leftLift.move_relative(30, 100);
	pros::delay(300);
	leftMtr.move_relative(-600, -75);
	leftMtrR.move_relative(-600, -75);
	rightMtr.move_relative(-600, -75);
	rightMtrR.move_relative(-600, -75);
	pros::delay(600);
	clawM.move_relative(-1200, -50);
	pros::delay(500);
}
*/

// Left win point
void Rauton() {
	arms::chassis::move(5, 100);
	arms::chassis::move(1, 50);
	clawM.move_relative(140, 75);
	clawM.move_relative(-140, -75);
	arms::chassis::move(-5, 100);
	arms::chassis::move(-1, 50);
}

// Yellow goal
void Yauton() {
	arms::chassis::move(38, 100);
	arms::chassis::move(10, 50);
	pros::delay(300);
	clawM.move_relative(200, 100);
	pros::delay(300);
	arms::chassis::move(-46, 100);
	pros::delay(300);
	clawM.move_relative(-200, -100);
	pros::delay(300);
	arms::chassis::move(-1, 50);
}

// Right win point
void Lauton() {
	clawM.move_relative(140, 50);
	clawM.move_relative(-140, -50);
}

void Sauton() {
	leftMtr.move_absolute(2850, 200);
	leftMtrR.move_absolute(1800, 200);
	rightMtr.move_absolute(2850, 200);
	rightMtrR.move_absolute(1800, 200);
	// 	Drivetrain.driveFor(forward, 42, inches, 75, velocityUnits::pct);
	// 	Claw.spinFor(forward, 200, degrees, 50, velocityUnits::pct);
	// 	Drivetrain.driveFor(reverse, 44, inches, 75, velocityUnits::pct);
	// 	Claw.spinFor(reverse, 200, degrees, 50, velocityUnits::pct);
	// 	Drivetrain.driveFor(reverse, 7, inches, 75, velocityUnits::pct);
	// 	Drivetrain.turnFor(right, 70, degrees);
	// 	Drivetrain.driveFor(forward, 26, inches, 75, velocityUnits::pct);
	// 	Claw.spinFor(forward, 200, degrees, 50, velocityUnits::pct);
	// 	Drivetrain.turnFor(left, 80, degrees);
	// 	Drivetrain.driveFor(forward, 90, inches, 75, velocityUnits::pct);
	// 	Claw.spinFor(reverse, 200, degrees, 50, velocityUnits::pct);
	// 	Drivetrain.turnFor(right, 70, degrees);
	// 	Drivetrain.driveFor(reverse, 90, inches, 75, velocityUnits::pct);
}

void trollingSkills() {
	arms::pid::linear();
	arms::chassis::turn(180, 50);
	arms::chassis::move(5, 100);
	arms::pid::init();
}

// Auton Selector Logic
void autonomous() {
	switch (arms::selector::auton) {
		case -1:
			trollingSkills();
			break;
		case 0:
			Sauton();
			break;
		case 1:
			Yauton();
			break;
		case 2:
			Lauton();
			break;
		case 3:
			Rauton();
			break;
		case 4:
			break;
		default:
			break;
	}
}
