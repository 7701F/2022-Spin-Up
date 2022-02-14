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

// Declare controller
extern pros::Controller master;

// Declare drive motors
extern pros::Motor leftMtr;
extern pros::Motor rightMtr;
extern pros::Motor leftMtrR;
extern pros::Motor rightMtrR;

// Declare lift motors
extern okapi::MotorGroup liftMotors;

// Declare grabby motors
extern pros::Motor clawM;
extern pros::Motor ringM;

// Declare winch motors
extern pros::Motor winchM;

// Sensors Sensor
extern pros::Imu imu_sensor;
extern pros::Distance distanceR;

// Vision Sensor
extern pros::Vision vision_sensor;
extern pros::vision_signature_s_t RED_SIG;
extern pros::vision_signature_s_t BLU_SIG;
extern pros::vision_signature_s_t YLW_SIG;

// Pneumatics
extern pros::ADIDigitalOut clawP;
extern pros::ADIDigitalOut AWP;

#endif
