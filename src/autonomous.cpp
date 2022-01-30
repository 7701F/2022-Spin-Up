/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "main.h"
#include "motors.h"

// Drive forward AND grab and pull tower auton
/*
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

// Right win point
void Rauton() {
	arms::chassis::move(15, 80);
	clawM.move_relative(200, 100);
	pros::delay(300);
	rightLift.move_relative(30, 100);
	leftLift.move_relative(30, 100);
	pros::delay(300);
	arms::chassis::move(-15, 80);
	arms::chassis::turn(-60, 80);
	clawM.move_relative(-200, -75);
}

// Yellow goal
void Yauton() {
	arms::chassis::move(51, 100);
	clawM.move_relative(200, 100);
	pros::delay(300);
	arms::chassis::move(-51, 100);
	// clawM.move_relative(-200, -100);
	pros::delay(300);
	arms::chassis::move(-1, 100);
	// arms::chassis::move(5, 50);
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
	arms::chassis::turn(-80, 50);
	arms::chassis::move(60, 80);
	clawM.move_relative(210, 50);
	pros::delay(300);
	rightLift.move_relative(30, 100);
	leftLift.move_relative(30, 100);
	pros::delay(500);
	arms::chassis::move(-60, 80);
}

void Sauton() {
	arms::chassis::move(46, 80);
	clawM.move_relative(200, 100);
	pros::delay(300);
	arms::chassis::move(-46, 80);
	clawM.move_relative(-200, -50);
	pros::delay(300);
	arms::chassis::move(-9, 80);
	arms::chassis::turn(64, 50);
	arms::chassis::move(30, 80);
	clawM.move_relative(200, 100);
	pros::delay(300);
	arms::chassis::turn(-70, 50);
	arms::chassis::move(90, 80);
	clawM.move_relative(-200, -50);
	pros::delay(300);
	arms::chassis::turn(94, 50);
	arms::chassis::move(-90, 80);
}

void trollingSkills() {
	leftMtr.move_absolute(2850, 200);
	leftMtrR.move_absolute(1800, 200);
	rightMtr.move_absolute(2850, 200);
	rightMtrR.move_absolute(1800, 200);
}

void winchTest() {
	winchM.move_relative(-2091, -100);
	pros::delay(3250);
	arms::chassis::move(-45, 50);
	winchM.move_relative(468, 100);
	pros::delay(1000);
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
std::string autonst[5] = {"YLW Goal", "R WP", "L WP", "Calibrate Auton"};
void autonomous() {
    // Log which auton we ran to console for debugging
	std::string selAuton = autonst[abs(arms::selector::auton)];

	// master.print(1, 0, "Auton: %s\n", selAuton.c_str());
	printf("Auton Int: %d Auton Str: %s\n", arms::selector::auton, selAuton.c_str());

    // Auton Selector Logic
	switch (arms::selector::auton) {
		case -4:
			arms::chassis::move(1, 50);
			break;
		case -3:
			Lauton();
			break;
		case -2:
			Rauton();
			break;
		case -1:
			Yauton();
			break;
		case 0:
			Sauton();
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
			// arms::chassis::turn(90, 50);
			winchTest();
			break;
		default:
			break;
	}
}
