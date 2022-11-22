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
#include "main.h"

/* Controller */
pros::Controller master(pros::E_CONTROLLER_MASTER);

/* Drive Motors */
pros::Motor rightMtr(8, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightMtrR(7, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftMtr(6, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftMtrR(5, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_DEGREES);

/* Game System Motors */
pros::Motor fw(12, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor conveyor(13, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor roller(4, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_COUNTS);

/* Pistons */
pros::ADIDigitalOut indexer('G');
pros::ADIDigitalOut endgame('H');

/* Sensors */
pros::Distance indexerSensor(2);
pros::Optical rollerSensor(3);
pros::IMU imu_sensor(1);

/* LEDs */
// sylib::Addrled indexLights(22, 2, 64);

/* Filters */
sylib::MedianFilter hueFilter(5, 2, 1);
sylib::MedianFilter distanceFilter(5, 2, 1);
