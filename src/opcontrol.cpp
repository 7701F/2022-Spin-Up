/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "main.h"

/*
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	liftMotors.moveRelative(30, 100);
	arms::lift::waitUntilSettled();
	liftMotors.tarePosition();
	liftMotors.moveRelative(30, 100);

	// Run Loop
	while (true) {
		/* Steering
		 * Handled by ARMS logic that has deadzones
		 */
		arms::chassis::arcade(master.get_analog(ANALOG_LEFT_Y) * (double)100 / 127,
		                      master.get_analog(ANALOG_RIGHT_X) * (double)100 / 127);
		/* Autonomous Manual Trigger
		 * If the robot is not connected to competition control
		 * and the button is pressed, the robot will the autonomous
		 * routine to allow for easy testing.
		 */
		if (master.get_digital_new_press(DIGITAL_X) && !pros::competition::is_connected())
			autonomous();

		/* Lift, Claw, and Winch Controls
		 * Controls for game specific functions
		 */
		gameSystemControls();

		// Brake System
		// The brake system is a safety feature that prevents the robot from being
		// pushed by other robots. Uses basic logic for toggle button
		if (master.get_digital_new_press(DIGITAL_B) == 1) {
			pbrake = !pbrake;
		}
		motorBrake(pbrake);

		// Lastly, delay
		pros::delay(2);
	}
}
