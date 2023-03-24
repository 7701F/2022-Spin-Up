/*
  Copyright (c) 2019-2023 7701F

  This software is provided 'as-is', without any express or implied warranty. In no event
  will the authors be held liable for any damages arising from the use of this software.
*/
#pragma once
#ifndef _7701F_HEAD_H_
#define _7701F_HEAD_H_

#include "main.h"
// clang-format off
#include "ARMS/config.h"
// clang-format on

// dependencies
#include <sstream>
#include <string>

// Declarations

/* Controller */
inline pros::Controller master(pros::E_CONTROLLER_MASTER);

/* Game System Motors */
inline pros::Motor fw(18, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_COUNTS);
inline pros::Motor conveyor(10, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);

/* Pistons */
inline pros::ADIDigitalOut indexer('G');

// endgame
inline pros::ADIDigitalOut endgame2('F');
inline pros::ADIDigitalOut endgame('H');

inline pros::ADIDigitalOut angler('A');

/* Sensors */
inline pros::Distance indexerSensor(19);
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
	if (sensorDistance > 155) {
		return 0;
	} else if (sensorDistance > 125) {
		return 1;
	} else if (sensorDistance > 80) {
		return 2;
	} else {
		return 3;
	}
}

/// @brief Gets the color of the roller
/// @return 1 = blue, 2 = red, 3 = unknown
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
inline bool pbrake = false;

// Game System Variables
// flywheel speed state
inline bool fwON = false;

// firing piston state
inline bool pistonState = false;
inline bool prevPistonState = false;
inline bool indexState = false;

// endgame piston state
inline bool EpistonState = false;
inline bool EprevPistonState = false;
inline bool ApistonState = false;
inline bool AprevPistonState = false;

inline bool endgameState = false;
inline bool aState = false;

// Declare driver functions.
void prosBrake(bool on, int type);
void prosBrake(bool on);

// Declare game system functions.
void fireDisc();
void toggleEndgame();
void toggleAngler();

namespace deFenestration {

/* program version definition */
const std::string CODENAME = "DF23-6M-W";

} // namespace deFenestration

#endif // _7701F_HEAD_H_
