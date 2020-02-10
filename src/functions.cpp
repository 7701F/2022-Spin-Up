/**
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "main.h"

// Distance in inches, Speed in rpms, Wait in milliseconds
void drive(double distance, int speed, int wait) {

    double wheel_radius = 2.065; //inches
    double const pi = 3.14159265;
    //1 rotation will move the robot 2*pi*wheel_radius inches
    double rotations = distance/(pi*2*wheel_radius);
    left_mtr.move_relative(rotations, speed);
    right_mtr.move_relative(rotations, speed);

    rotations += left_mtr.get_position();

    while (!((left_mtr.get_position() < rotations + 0.5) && (left_mtr.get_position() > rotations - 0.5 ))) {
        pros::delay(5);
	}

    pros::delay(wait);

}

// Degrees of turn.  Speed is RPM, Wait is milliseconds
void turn(double degrees, int speed, int wait) {

    double one_rotation_turn_degrees = 115; //customize to your robot
    double rotations = degrees/one_rotation_turn_degrees;
    left_mtr.move_relative(rotations, speed);
    right_mtr.move_relative(-rotations, speed);

    rotations += left_mtr.get_position();

    while (!((left_mtr.get_position() < rotations + 0.5) && (left_mtr.get_position() > rotations -0.5 ))) {
        pros::delay(20);
    }
    
    pros::delay(wait);

}

// angle the tray
void angle(double degrees, int speed, int wait) {

    double one_rotation_turn_degrees = 115; //customize to your robot
    double rotations = degrees/one_rotation_turn_degrees;
    angler_mtr.move_relative(rotations, speed);

    rotations += angler_mtr.get_position();

    while (!((angler_mtr.get_position() < rotations + 0.5) && (angler_mtr.get_position() > rotations -0.5 ))) {
        pros::delay(20);
    }
    
    pros::delay(wait);

}

// rotate the intakes
void rotate(double degrees, int speed, int wait) {

    double one_rotation_turn_degrees = 115; //customize to your robot
    double rotations = degrees/one_rotation_turn_degrees;
    intake_mtr.move_relative(rotations, speed);
	intake1_mtr.move_relative(rotations, speed);

    rotations += intake_mtr.get_position();

    while (!((intake_mtr.get_position() < rotations + 0.5) && (intake_mtr.get_position() > rotations -0.5 ))) {
        pros::delay(20);
    }
    
    pros::delay(wait);

}
