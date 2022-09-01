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

// Game System Motors
okapi::Motor intakeM(14, true, okapi::AbstractMotor::gearset::blue,
					okapi::AbstractMotor::encoderUnits::degrees);
// Sensors
pros::Imu imu_sensor(1);

// Vision
pros::Vision vision_sensor(7, pros::E_VISION_ZERO_CENTER);
pros::Distance distance_sensor(8);

// Pneumatics
// pros::ADIDigitalOut clawP('A');
// pros::ADIDigitalOut AWP('B');
