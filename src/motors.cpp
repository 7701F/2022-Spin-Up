/*
  Copyright (c) 2019-2022 7701F

  This software is provided 'as-is', without any express or implied warranty. In no event will
  the authors be held liable for any damages arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose, including commercial
  applications, and to alter it and redistribute it freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you wrote the
  original software. If you use this software in a product, an acknowledgment (see the following)
  in the product documentation is required.

  Portions Copyright (c) 2019-2022 7701F

  2. Altered source versions must be plainly marked as such, and must not be misrepresented as
  being the original software.

  3. This notice may not be removed or altered from any source distribution.
*/

#include "7701.h"
#include "main.h"

/* Controller */
pros::Controller master(pros::E_CONTROLLER_MASTER);

/* Drive Motors */
okapi::Motor rightMtr(20, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor rightMtrR(19, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor leftMtr(13, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor leftMtrR(12, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);

/* Drive Motor Groups */
okapi::MotorGroup rightMotors({rightMtr, rightMtrR});
okapi::MotorGroup leftMotors({leftMtr, leftMtrR});

/* Game System Motors */
okapi::Motor flywheel(12, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor conveyor(13, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);

okapi::Motor intake(5, true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);

/* Sensors */
okapi::IMU imu_sensor(1);
okapi::DistanceSensor distance_sensor(8);
