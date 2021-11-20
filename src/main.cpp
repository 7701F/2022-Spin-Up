/*
 * Copyright (c) 2019-2021, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	display();
	rightLift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	leftLift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	clawM.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

void autonomous()
{
	/* Templates
		drive(60,100,1000);
		turn(-360,100,1000);
	*/

	// drive(150, 200, 50);
	// turn(100, 75, 50);
	leftMtr.move_relative(300, 75);
	leftMtrR.move_relative(300, 75);
	rightMtr.move_relative(300, 75);
	rightMtrR.move_relative(300, 75);
	pros::delay(300);
	clawM.move_relative(1200, 600);
	rightLift.move_relative(62, -65);
	leftLift.move_relative(62, 65);
	pros::delay(300);
	leftMtr.move_relative(-600, -75);
	leftMtrR.move_relative(-600, -75);
	rightMtr.move_relative(-600, -75);
	rightMtrR.move_relative(-600, -75);
	pros::delay(600);
	leftMtr.move_relative(-360, -150);
	leftMtrR.move_relative(-360, -150);
	rightMtr.move_relative(360, 150);
	rightMtrR.move_relative(360, 150);
	pros::delay(600);
	clawM.move_relative(-1200, -600);
	pros::delay(500);
}
