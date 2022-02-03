/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <array>

#include "main.h"

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
	arms::chassis::move(54, 100);
	clawM.move_relative(200, 100);
	pros::delay(300);
	arms::chassis::move(-55, 100);
	// clawM.move_relative(-200, -100);
	// pros::delay(300);
	// arms::chassis::move(-1, 100);
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
	arms::chassis::turn(-80, 60);
	arms::chassis::move(50, 100);
	arms::chassis::move(10, 75);
	clawM.move_relative(210, 100);
	pros::delay(300);
	rightLift.move_relative(30, 75);
	leftLift.move_relative(30, 75);
	pros::delay(500);
	arms::chassis::move(-60, 100);
}

// Programming Skills
void Sauton() {
	winchM.move_relative(-2065, -100);
	pros::delay(3250);
	arms::chassis::move(-30, 50);
	winchM.move_relative(1070, 100);
	pros::delay(1250);
	arms::chassis::move(28, 60);
	arms::chassis::turn(150, 50);
	arms::chassis::move(65, 80);
	clawM.move_relative(210, 50);
	pros::delay(350);
	pros::delay(500);
	arms::chassis::move(-60, 80);
	arms::chassis::turn(45, 50);
	clawM.move_relative(-210, 50);
	pros::delay(300);
	arms::chassis::turn(-85, 50);
	arms::chassis::move(65, 80);
	arms::chassis::move(50, 80);
}

// Programming Skills 2.0
void Sauton2() {
	winchM.move_relative(-2065, -100);
	pros::delay(3250);
	arms::chassis::move(-30, 50);
	winchM.move_relative(1070, 100);
	pros::delay(1250);
	arms::chassis::move(28, 60);
	arms::chassis::turn(150, 50);
	arms::chassis::move(65, 80);
	clawM.move_relative(210, 50);
	pros::delay(300);
	arms::chassis::move(-60, 80);
	arms::chassis::turn(45, 50);
	clawM.move_relative(-210, 50);
	pros::delay(300);
	arms::chassis::turn(-85, 50);
	arms::chassis::move(65, 80);
	clawM.move_relative(210, 50);
	pros::delay(300);
	arms::chassis::move(50, 80);
	clawM.move_relative(-210, 50);
	pros::delay(300);
	arms::chassis::move(-50, 80);
	arms::chassis::turn(-45, 50);
	arms::chassis::move(50, 80);
	clawM.move_relative(210, 50);
	pros::delay(300);
	arms::chassis::turn(90, 50);
	arms::chassis::moveAsync(50, 80);
	winchM.move_relative(1070, 100);
	pros::delay(1250);
	clawM.move_relative(-210, 50);
	pros::delay(200);
	arms::chassis::turn(-180, 50);
	arms::chassis::move(100, 80);
	arms::chassis::turn(-50, 80);
	arms::chassis::move(6, 80);
	clawM.move_relative(-210, 50);
	pros::delay(200);
	arms::chassis::move(-6, 80);
	arms::chassis::turn(-50, 80);
	arms::chassis::move(100, 80);
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
	// Log which auton we ran to console for debugging
	std::string selAuton = arms::selector::b[abs(arms::selector::auton)];

	// master.print(1, 0, "Auton: %s\n", selAuton.c_str());
	printf("Auton Int: %d Auton Str: %s\n", arms::selector::auton, selAuton.c_str());

	// Auton Selector Logic
	switch (arms::selector::auton) {
		case -4:
			arms::chassis::move(5, 50);
			arms::chassis::turn(90, 50);
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
			arms::odom::reset();
			arms::odom::move({30, 30});
			break;
		default:
			break;
	}

	printf("Successfully ran auton: %s\n", arms::selector::b[abs(arms::selector::auton)]);
}
