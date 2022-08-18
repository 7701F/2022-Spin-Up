/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "main.h"

#ifndef MOTORS_H_
#define MOTORS_H_

// Controller
extern pros::Controller master(pros::E_CONTROLLER_MASTER);

// Drive Motors
extern okapi::Motor rightMtr(20, true, okapi::AbstractMotor::gearset::green,
                       okapi::AbstractMotor::encoderUnits::degrees);
extern okapi::Motor leftMtr(19, true, okapi::AbstractMotor::gearset::green,
                       okapi::AbstractMotor::encoderUnits::degrees);
extern okapi::Motor rightMtrR(18, true, okapi::AbstractMotor::gearset::green,
                       okapi::AbstractMotor::encoderUnits::degrees);
extern okapi::Motor leftMtrR(17, true, okapi::AbstractMotor::gearset::green,
                       okapi::AbstractMotor::encoderUnits::degrees);

// Drive Motor Groups
extern okapi::MotorGroup rightMotors({rightMtr, rightMtrR});
extern okapi::MotorGroup leftMotors({leftMtr, leftMtrR});

// Sensors
extern pros::Imu imu_sensor(1);
extern pros::Distance distanceR;

// Vision
extern pros::Vision vision_sensor;

#endif
