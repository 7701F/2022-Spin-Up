/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "main.h"

#include <sstream>

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// ARMS & Controller init and reset IMU sensor
	arms::chassis::init();

	// Controller Status Display
	pros::Task controllerTask{[=] {
		master.clear();

		std::string selAuton;
		while (true) {
			// Only print every 50ms, the controller text update rate
			// is slow
			selAuton = arms::selector::b[abs(arms::selector::auton)];

			std::stringstream autonstr;
			autonstr << "Auton: " << arms::selector::auton << "\r";
			std::stringstream brakestr;
			brakestr << "Brake: " << (pbrake ? "ON" : "OFF") << "\r";

			master.print(0, 0, autonstr.str().c_str());
			pros::delay(50);
			master.print(1, 0, brakestr.str().c_str());
			pros::delay(50);
			master.print(2, 0, "Distance: %d", distanceR.get());
			// master.print(2, 0, "Gyro: %f\r",
			// imu_sensor.get_heading());
			printf("Distance: %d\n", distanceR.get());
			pros::delay(200);
		}
	}};

	// ARMS Auton Selector
	arms::selector::init();

	// Set brakes on to active bold
	liftMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	winchM.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	static int count = 1;
	printf("Disabled called %d\n", count++);

	if (ringTask) {
		pros::Task(ringTask).remove();
		ringTask = (pros::task_t)NULL;
	}

	while (true) {
		pros::delay(1000);
	}
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	static int count = 1;
	printf("Comp Init called %d\n", count++);
}
