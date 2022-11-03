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

// deFenestration Auton System
namespace deFenestration::Vision {
void init();

int32_t mmToInch();
} // namespace deFenestration::Vision

// deFenestration Flywheel System
namespace deFenestration::Flywheel {
void FwMotorSet(int value);

double FwMotorEncoderGet();

void FwVelocitySet(int velocity, float predicted_drive);

void FwCalculateSpeed();

void FwControlUpdateVelocityTbh();

void FwControlTask();
} // namespace deFenestration::Flywheel

// Declare drive system variables.
inline bool pbrake = true;

// Declare driver functions
void customBrake(bool pbrake);
void prosBrake(bool pbrake);
void FwControlTask();

/* Controller */
extern pros::Controller master;

/* Drive Motor Groups */
extern okapi::MotorGroup rightMotors;
extern okapi::MotorGroup leftMotors;

/* Game System Motors */

/* Disk Launcher Motors */
extern okapi::Motor flywheel;
extern okapi::Motor conveyor;

/* Disk Intake Motors */
extern okapi::Motor intake;

/* Sensors */
extern okapi::IMU imu_sensor;
extern okapi::DistanceSensor distance_sensor;

/* Display */
void display();
