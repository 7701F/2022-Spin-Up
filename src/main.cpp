/**
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
        Not really needed anymore since we just have a one cube auton now.

        drive(60,100,1000);
        turn(-360,100,1000);
        eject(-180,100,1000);
        rotate(-60,100,1000);
    */
	// turn(360, 200, 200);
	// rotate(200, 200, 20);
	drive(10, 100, 20);
	turn(90, 200, 20);
	drive(-10, 100, 20);
	// eject(2000, 600, 20);

	// intake_mtr.move_velocity(175);
	// intake1_mtr.move_velocity(-175);

	pros::delay(500);

	// intake_mtr.move_velocity(0);
	// intake1_mtr.move_velocity(0);
}
