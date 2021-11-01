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
	rightLift.move_velocity(-200);
	leftLift.move_velocity(-200);
	pros::delay(100);
	// rightLift.move_velocity(0);
	// leftLift.move_velocity(0);
	rightLift.set_zero_position(rightLift.get_position());
	leftLift.set_zero_position(leftLift.get_position());
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

	drive(60, 200, 50);
	turn(50, 75, 50);

	pros::delay(500);
}
