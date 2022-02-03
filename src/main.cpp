/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "main.h"

#include "opfunctions.h"

// Controller Auton Indicator
int scrcount = 1;
bool ctrlScrBool = false;
void ctrlrScr() {
	std::string selAuton = arms::selector::b[abs(arms::selector::auton)];

	if (!(scrcount % 25)) {
		// Only print every 50ms, the controller text update rate is slow
		if (ctrlScrBool == true) {
			master.clear();
			master.print(0, 0, "Auton: %s", selAuton.c_str());
			printf("auton log");
			ctrlScrBool = !ctrlScrBool;
		} else {
			master.clear();
			master.print(0, 0, "Brake: %s", (pbrake ? "ON" : "OFF"));
			printf("brake log");
			ctrlScrBool = !ctrlScrBool;
		}
	}

	scrcount++;
	pros::delay(200);
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// ARMS & Controller init and reset IMU sensor
	arms::chassis::init();
	arms::odom::init();
	arms::pid::init();
	imu_sensor.reset();
	pros::Task controllerTask{ctrlrScr, "Controller Display"};

	// Set display
	if (!pros::competition::is_connected()) display();

	// Set brakes on to active bold
	rightLift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	leftLift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	clawM.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	winchM.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	printf("Disabled");
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
	arms::selector::init();
}
