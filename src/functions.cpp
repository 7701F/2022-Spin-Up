/**
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "main.h"

// // Distance in inches, Speed in rpms, Wait in milliseconds
// void drive(double distance, int speed, int wait)
// {
// 	double wheel_radius = 2.065; // inches
// 	double const pi =
// 		3.141592653589793238462643383279502884197169399375105820974944592307816406286; // 1 rotation will move the robot 2*pi*wheel_radius inches
// 	double rotations = distance / (pi * 2 * wheel_radius);

// 	leftMtr.move_relative(rotations, speed);
// 	rightMtr.move_relative(rotations, speed);

// 	rotations += leftMtr.get_position();

// 	while (!((leftMtr.get_position() < rotations + 0.5) &&
// 			 (leftMtr.get_position() > rotations - 0.5)))
// 	{
// 		pros::delay(5);
// 	}

// 	pros::delay(wait);
// }

// // Degrees of turn.  Speed is RPM, Wait is milliseconds
// void turn(double degrees, int speed, int wait)
// {
// 	double one_rotation_turn_degrees = 115; // customize to your robot
// 	double rotations = degrees / one_rotation_turn_degrees;
// 	leftMtr.move_relative(rotations, speed);
// 	rightMtr.move_relative(-rotations, speed);

// 	rotations += leftMtr.get_position();

// 	while (!((leftMtr.get_position() < rotations + 0.5) &&
// 			 (leftMtr.get_position() > rotations - 0.5)))
// 	{
// 		pros::delay(20);
// 	}

// 	pros::delay(wait);
// }

// // eject spheres
// void eject(double degrees, int speed, int wait)
// {

// 	double one_rotation_turn_degrees = 115; // customize to your robot
// 	double rotations = degrees / one_rotation_turn_degrees;

// 	drive(3, 200, 1);
// 	elevator_mtr.move_relative(rotations, speed);
// 	elevator1_mtr.move_relative(rotations, speed);
// 	// elevator_mtr.move_velocity(600);
// 	// elevator1_mtr.move_velocity(-600);

// 	rotations += elevator_mtr.get_position();

// 	while (!((elevator_mtr.get_position() < rotations + 0.5) &&
// 			 (elevator1_mtr.get_position() > rotations - 0.5)))
// 	{
// 		pros::delay(20);
// 	}

// 	pros::delay(wait);
// }

// rotate the intakes
// void rotate(double degrees, int speed, int wait)
// {

// 	double one_rotation_turn_degrees = 115; // customize to your robot
// 	double rotations = degrees / one_rotation_turn_degrees;
// 	intake_mtr.move_relative(rotations, speed);
// 	intake1_mtr.move_relative(rotations, speed);

// 	rotations += intake_mtr.get_position();

// 	while (!((intake_mtr.get_position() < rotations + 0.5) &&
// 			 (intake_mtr.get_position() > rotations - 0.5)))
// 	{
// 		pros::delay(20);
// 	}

// 	pros::delay(wait);
// }
