/*
 * Copyright (c) 2019-2021, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "main.h"

// Distance in inches, Speed in rpms, Wait in milliseconds
void drive(double distance, int speed, int wait)
{
	double wheel_radius = 2.065; // pi
	// 1 rotation will move the robot
	// 2 *pi *wheel_radius inches
	double rotations = distance / (M_PI * 2 * wheel_radius);

	leftMtr.move_relative(rotations, speed);
	rightMtr.move_relative(rotations, speed);
	leftMtrR.move_relative(rotations, speed);
	rightMtrR.move_relative(rotations, speed);

	rotations += leftMtr.get_position();

	while (!((leftMtr.get_position() < rotations + 0.5) && (leftMtr.get_position() > rotations - 0.5)))
	{
		pros::delay(5);
	}

	pros::delay(wait);
}

// Degrees of turn.  Speed is RPM, Wait is milliseconds
void turn(double degrees, int speed, int wait)
{
	double one_rotation_turn_degrees = 90;
	// customize to your robot
	double rotations = degrees / one_rotation_turn_degrees;
	leftMtr.move_relative(rotations, speed);
	rightMtr.move_relative(-rotations, speed);
	leftMtrR.move_relative(rotations, speed);
	rightMtrR.move_relative(-rotations, speed);

	rotations += leftMtr.get_position();

	while (!((leftMtr.get_position() < rotations + 0.5) && (leftMtr.get_position() > rotations - 0.5)))
	{
		pros::delay(20);
	}

	pros::delay(wait);
}
