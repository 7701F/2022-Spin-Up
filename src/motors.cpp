/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "main.h"

// Controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Driving Motors
pros::Motor leftMtr(20, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor leftMtrR(19, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor rightMtr(11, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor rightMtrR(12, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

// Lift Motors
okapi::Motor rightLift(8, true, okapi::AbstractMotor::gearset::red,
                       okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor leftLift(9, false, okapi::AbstractMotor::gearset::red,
                      okapi::AbstractMotor::encoderUnits::degrees);
okapi::MotorGroup liftMotors({rightLift, leftLift});

// Claw Motor
pros::Motor clawM(6, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);

// Winch Motor
pros::Motor winchM(15, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);

// Inertial Sensor
pros::Imu imu_sensor(1);
pros::Distance distanceR(21);

// Vision
pros::vision_signature_s_t RED_SIG =
    pros::Vision::signature_from_utility(1, 6255, 7309, 6782, -325, 223, -52, 3.000, 0);
pros::vision_signature_s_t YLW_SIG = pros::Vision::signature_from_utility(
    2, 351, 1099, 724, -3479, -2631, -3054, 3.000, 0);
pros::vision_signature_s_t BLU_SIG = pros::Vision::signature_from_utility(
    3, -3073, -2047, -2560, 7899, 12545, 10222, 3.000, 0);
pros::Vision vision_sensor(10, pros::E_VISION_ZERO_CENTER);

// AWP
pros::ADIDigitalOut puncher('A');
