/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "main.h"

// Driving Motors
pros::Motor leftMtr(20, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor rightMtr(11, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor leftMtrR(19, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor rightMtrR(12, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

// Lift Motors
pros::Motor rightLift(8, MOTOR_GEARSET_36, true, MOTOR_ENCODER_DEGREES);
pros::Motor leftLift(9, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);

// Claw Motor
pros::Motor clawM(16, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);

// Winch Motor
pros::Motor winchM(15, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);

// Inertial Sensor
pros::Imu imu_sensor(1);
