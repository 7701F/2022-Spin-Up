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
extern pros::Controller master;

// Drive Motors
extern okapi::Motor rightMtr;
extern okapi::Motor leftMtr;
extern okapi::Motor rightMtrR;
extern okapi::Motor leftMtrR;

// Drive Motor Groups
extern okapi::MotorGroup rightMotors;
extern okapi::MotorGroup leftMotors;

// Sensors
extern pros::Imu imu_sensor;

// Vision
extern pros::Vision vision_sensor;

#endif
