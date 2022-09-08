/*
  Copyright (c) 2019-2022, Michael Gummere.
  All rights reserved.

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated and is required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "api.h"
#include "okapi/api.hpp"

#ifndef MOTORS_H_
#define MOTORS_H_

// Controller
extern pros::Controller master;

// Drive Motors
extern okapi::Motor hMtr;
extern okapi::MotorGroup rightMotors;
extern okapi::MotorGroup leftMotors;

// Game System Motors

// Sensors
extern pros::Imu imu_sensor;
extern pros::Distance distance_sensor;
extern pros::Distance distance_sensor1;

#endif
