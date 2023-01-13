/*
  Copyright (c) 2019-2023 7701F

  This software is provided 'as-is', without any express or implied warranty. In no event will
  the authors be held liable for any damages arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose, including commercial
  applications, and to alter it and redistribute it freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you wrote the
  original software. If you use this software in a product, an acknowledgment (see the following)
  in the product documentation is required.

  Portions Copyright (c) 2019-2023 7701F

  2. Altered source versions must be plainly marked as such, and must not be misrepresented as
  being the original software.

  3. This notice may not be removed or altered from any source distribution.
*/
#include "main.h"
#include "settings.h"
namespace deFenestration {

/* Display */
void display();

} // namespace deFenestration

// Declarations
/* Controller */
extern pros::Controller master;
extern pros::Controller partner;

/* Game System Motors */
extern pros::Motor fw;
extern pros::Motor conveyor;
extern pros::Motor conv2;

/* Pistons */
extern pros::ADIDigitalOut indexer;
extern pros::ADIDigitalOut endgame;

/* Sensors */
extern pros::Distance indexerSensor;
extern pros::Optical rollerSensor;
extern pros::IMU imu_sensor;

/* LEDs */
// extern sylib::Addrled;

/* Filters */
extern sylib::MedianFilter hueFilter;
extern sylib::MedianFilter distanceFilter;

// deFenestration Flywheel System

// Set the encoder ticks per revolution
inline float ticks_per_rev = 360;

// Encoder
inline long encoder_counts;      ///< current encoder count
inline long encoder_counts_last; ///< current encoder count

// velocity measurement
inline float motor_velocity; ///< current velocity in rpm
inline long millis_last;     ///< Time of last velocity calculation

// TBH control algorithm variables
inline long target_velocity; ///< target_velocity velocity
inline float current_error;  ///< error between actual and target_velocity velocities
inline float last_error;     ///< error last time update called
inline float gain;           ///< gain
inline float drive;          ///< final drive out of TBH (0.0 to 1.0)
inline float drive_at_zero;  ///< drive at last zero crossing
inline long first_cross;     ///< flag indicating first zero crossing
inline float drive_approx;   ///< estimated open loop drive

// final motor drive
inline long motor_drive; ///< final motor control value

inline int current_time;
inline float delta_ms;
inline int delta_enc;

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
inline bool bypass = false;
inline bool curve2 = false;

// Game System Variables

// flywheel speed state
inline bool flywheelState = false;
inline bool flywheelThirdPosState = false;
inline bool flywheel4PosState = false;
inline bool flywheelOff = false;
inline bool fwON = false;

// firing piston state
inline bool pistonState = false;
inline bool prevPistonState = false;
inline bool indexState = false;

// endgame piston state
inline bool EpistonState = false;
inline bool EprevPistonState = false;
inline bool endgameState = false;

// Declare driver functions.
void prosBrake(bool on, int type);
void prosBrake(bool on);

// Declare game system functions.
int getFrisbeesInIndexer();
int getRollerColor();
void fireDisc();
