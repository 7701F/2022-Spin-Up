/*
  Copyright (c) 2019-2023 7701F

  This software is provided 'as-is', without any express or implied warranty. In no event
  will the authors be held liable for any damages arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose, including
  commercial applications, and to alter it and redistribute it freely, subject to the
  following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you
  wrote the original software. If you use this software in a product, an acknowledgment
  (see the following) in the product documentation is required.

  Portions Copyright (c) 2019-2023 7701F

  2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original software.

  3. This notice may not be removed or altered from any source distribution.
*/
#ifndef _7701F_HEAD_H_
#define _7701F_HEAD_H_

#include "main.h"
// clang-format off
#include "ARMS/config.h"
// clang-format on
#include "settings.h"

// dependencies
#include <sstream>

namespace deFenestration::display {

/* create custom display */
void create();

/* destroy custom display*/
// void destroy();

} // namespace deFenestration::display

// Declarations

/* Controller */
inline pros::Controller master(pros::E_CONTROLLER_MASTER);

/* Game System Motors */
inline pros::Motor fw(13, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_COUNTS);
inline pros::Motor conveyor(10, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);

/* Pistons */
inline pros::ADIDigitalOut indexer('G');

// endgame
inline pros::ADIDigitalOut endgame2('F');
inline pros::ADIDigitalOut endgame('H');

/* Sensors */
inline pros::Distance indexerSensor(16);
inline pros::Optical rollerSensor(9);

/* LEDs */
// inline sylib::Addrled indexLights(22, 2, 64);

/* Filters */
inline sylib::MedianFilter hueFilter(5, 2, 1);
inline sylib::MedianFilter distanceFilter(5, 2, 1);

/* Util Functions */

/* Gets the # of Frisbees in the Indexer */
inline int getDiscsInIndexer() {
	int sensorDistance = distanceFilter.filter(indexerSensor.get());
	if (sensorDistance > 105) {
		return 0;
	} else if (sensorDistance > 90) {
		return 1;
	} else if (sensorDistance > 70) {
		return 2;
	} else {
		return 3;
	}
}

/* Get the color of the Roller from the Optical Sensor.

 * 0 = no color.
 * 1 = blue.
 * 2 = red.
 * 3 = idk.
 */
inline int getRollerColor() {
	if (rollerSensor.get_proximity() < 200) {
		return 0;
	}

	double hue = hueFilter.filter(rollerSensor.get_hue());
	if (hue < 265 && hue > 225) {
		return 1; // blue
	} else if (hue < 20 && hue > 340) {
		return 2; // red
	} else {
		return 3; // lol it doesnt know
	}
	return 0;
}

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

// Game System Variables
// flywheel speed state
inline bool flywheel2PosState = false;
inline bool flywheel3PosState = false;
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
void fireDisc();
void toggleEndgame();
#endif // _7701F_HEAD_H_
