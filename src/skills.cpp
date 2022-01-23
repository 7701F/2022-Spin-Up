/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "main.h"
// #include "autoncontrol.h"

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

void skills_auton() {
	/* Templates
		drive(60,100,1000);
		turn(-360,100,1000);
	*/

	// drive(38,200,1000);
	leftMtr.move_absolute(2850, 200);
	leftMtrR.move_absolute(1800, 200);
	rightMtr.move_absolute(2850, 200);
	rightMtrR.move_absolute(1800, 200);
}

// Drive forward AND grab and pull tower auton
void game_autonomous()
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

void new_game_auton() {

}

// Auton Selector Logic
void autonomous()
{
	switch (selector::auton)
	{
	case 1:
		game_autonomous();
		break;
	case 2:
		skills_auton();
		break;
	case 3:
		new_game_auton();
	default:
		break;
	}
	// if (auton == false)
	// {
	// 	game_autonomous();
	// }
	// else if (auton == true)
	// {
	// 	skills_auton();
	// }
	// else
	// {
	// 	return;
	// }
}
