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

// Drive Motors
okapi::Motor rightMtr(20, true, okapi::AbstractMotor::gearset::green,
                      okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor leftMtr(19, true, okapi::AbstractMotor::gearset::green,
                     okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor rightMtrR(18, true, okapi::AbstractMotor::gearset::green,
                       okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor leftMtrR(17, true, okapi::AbstractMotor::gearset::green,
                      okapi::AbstractMotor::encoderUnits::degrees);

// Drive Motor Groups
okapi::MotorGroup rightMotors({rightMtr, rightMtrR});
okapi::MotorGroup leftMotors({leftMtr, leftMtrR});

// Sensors
pros::Imu imu_sensor(1);

// Vision
pros::Vision vision_sensor(7, pros::E_VISION_ZERO_CENTER);

// Pneumatics
// pros::ADIDigitalOut clawP('A');
// pros::ADIDigitalOut AWP('B');
