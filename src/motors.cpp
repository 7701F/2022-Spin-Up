/**
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "main.h"

// Driving Motors
pros::Motor leftMtr(1, MOTOR_GEARSET_18, false, MOTOR_ENCODER_ROTATIONS);
pros::Motor rightMtr(2, MOTOR_GEARSET_18, true, MOTOR_ENCODER_ROTATIONS);
// pros::Motor leftMtrR(10,MOTOR_GEARSET_18,false,MOTOR_ENCODER_ROTATIONS);
// pros::Motor rightMtrR(9,MOTOR_GEARSET_18,true,MOTOR_ENCODER_ROTATIONS);

// Intake Motors
// Left Intake
pros::Motor intake_mtr(7, MOTOR_GEARSET_18, false, MOTOR_ENCODER_ROTATIONS);
// Right Intake
pros::Motor intake1_mtr(8, MOTOR_GEARSET_18, false, MOTOR_ENCODER_ROTATIONS);
// Front Elevator
pros::Motor elevator_mtr(9, MOTOR_GEARSET_06, false, MOTOR_ENCODER_ROTATIONS);
// Rear Elevator
pros::Motor elevator1_mtr(10, MOTOR_GEARSET_06, false, MOTOR_ENCODER_ROTATIONS);

// Intake Arm Motors
// pros::Motor intakearm_mtr(6,MOTOR_GEARSET_36,false,MOTOR_ENCODER_DEGREES);
// pros::Motor intakearm1_mtr(5,MOTOR_GEARSET_36,true,MOTOR_ENCODER_DEGREES);

// Angle Motor
// pros::Motor angler_mtr(1,MOTOR_GEARSET_36,false,MOTOR_ENCODER_ROTATIONS);
