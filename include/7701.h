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

namespace deFenestration {
/* Display */
void display();

/* Enable Show Screen */
const bool showScreen = true;
} // namespace deFenestration

// Declarations
/* Controller */
extern pros::Controller master;

/* Drive Motor Groups */
extern okapi::MotorGroup rightMotors;
extern okapi::MotorGroup leftMotors;

/* Game System Motors */
extern okapi::Motor fw;
extern okapi::Motor conveyor;
extern okapi::Motor roller;
extern pros::ADIDigitalOut indexer;

/* Sensors */
extern pros::Distance indexerSensor;
extern pros::Optical rollerSensor;
extern pros::IMU imu_sensor1;

/* Filters */
extern sylib::MedianFilter hueFilter;
extern sylib::MedianFilter distanceFilter;

// deFenestration Flywheel System
namespace deFenestration::Flywheel {
void FwMotorSet(int value);

double FwMotorEncoderGet();

void FwVelocitySet(int velocity, float predicted_drive);

float FwCalculateSpeed();

void FwControlUpdateVelocityTbh();

void FwControlTask();
} // namespace deFenestration::Flywheel

// Declare drive system variables.
inline bool pbrake = true;

// Declare driver functions.
void customBrake(bool pbrake);
void prosBrake(bool pbrake);

// Declare game system functions.
int getFrisbeesInIndexer();
int getRollerColor();
