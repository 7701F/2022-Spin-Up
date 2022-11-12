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

/* Config */
const bool debug = false;

/* Enable Show Screen */
const bool showScreen = true;
} // namespace deFenestration

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

// Declare driver functions
void customBrake(bool pbrake);
void prosBrake(bool pbrake);

/* Controller */
inline pros::Controller master(pros::E_CONTROLLER_MASTER);

/* Drive Motors */
inline okapi::Motor rightMtr(20, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
inline okapi::Motor rightMtrR(19, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
inline okapi::Motor leftMtr(17, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
inline okapi::Motor leftMtrR(18, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);

/* Drive Motor Groups */
inline okapi::MotorGroup rightMotors({rightMtr, rightMtrR});
inline okapi::MotorGroup leftMotors({leftMtr, leftMtrR});

/* Game System Motors */
inline okapi::Motor fw(12, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
inline okapi::Motor conveyor(13, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
inline okapi::Motor roller(5, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
inline pros::ADIDigitalOut indexer('A');

/* Sensors */
inline pros::Distance indexerSensor(11);
inline pros::Optical rollerSensor(3);
inline pros::IMU imu_sensor1(1);
// inline pros::IMU imu_sensor2(2);

inline sylib::MedianFilter hueFilter(5,2,1);
inline sylib::MedianFilter distanceFilter(5,2,1);

int getFrisbeesInIntake();

// namespace deFenestration {
// class IMU {
//  public:
// 	virtual void reset() {
// 		imu_sensor1.reset();
// 		// imu_sensor2.reset();

// 		while (imu_sensor1.is_calibrating() || imu_sensor2.is_calibrating()) {
// 			pros::delay(10);
// 		}
// 	};

// 	// Detirmine IMU offset
// 	virtual double offset() {
// 		int32_t offset = 0;
// 		double_t x = (imu_sensor1.get_pitch() - imu_sensor2.get_pitch());
// 		return x;
// 	};

// 	virtual double status() {
// 		double current_offset = offset();
// 		if (current_offset > 0) {
// 			return 1;
// 		} else if (current_offset < 0) {
// 			return -1;
// 		} else {
// 			return 0;
// 		}
// 	}

// 	// Determine IMU angle
// 	virtual double getHeading() {
// 		return (imu_sensor1.get_heading() + imu_sensor2.get_heading()) / 2;
// 	}

// 	// Turn to a specified angle
// 	virtual void turnToH(double target, double speed) {
// 		double target_heading = target;
// 		double current_heading = (imu_sensor1.get_heading() + imu_sensor2.get_heading()) / 2;

// 		double difference = abs(target_heading - current_heading);

// 		if (target_heading > current_heading) {
// 			while (target_heading != current_heading) {
// 				arms::chassis::turn(difference / 8, speed);
// 			}
// 		}
// 		if (target_heading < current_heading) {
// 			while (target_heading != current_heading) {
// 				arms::chassis::turn(-difference / 8, speed);
// 			}
// 		} else {
// 			// do nothing
// 		}
// 	}

// 	virtual void tare() {
// 		imu_sensor1.tare();
// 		imu_sensor2.tare();
// 	}
// };

// using Imu = IMU;

// } // namespace deFenestration
