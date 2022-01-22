/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef MOTORS_H_
#define MOTORS_H_

// Declare motors
extern pros::Motor leftMtr;
extern pros::Motor rightMtr;
extern pros::Motor leftMtrR;
extern pros::Motor rightMtrR;
extern pros::Motor rightLift;
extern pros::Motor leftLift;
extern pros::Motor clawM;
extern pros::Motor winchM;

// Not technically a motor :shrug:
extern pros::Imu imu_sensor;

#endif
