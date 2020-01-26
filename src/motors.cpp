/**
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "main.h"

// Driving Motors
pros::Motor left_mtr(12,MOTOR_GEARSET_18,false,MOTOR_ENCODER_ROTATIONS);
pros::Motor right_mtr(11,MOTOR_GEARSET_18,true,MOTOR_ENCODER_ROTATIONS);    
// Arm Motors
pros::Motor arm_mtr(20,MOTOR_GEARSET_36,false,MOTOR_ENCODER_ROTATIONS);
pros::Motor arm1_mtr(10,MOTOR_GEARSET_36,false,MOTOR_ENCODER_ROTATIONS);

// Claw Motor
pros::Motor claw_mtr(18,MOTOR_GEARSET_36,false,MOTOR_ENCODER_ROTATIONS);
