/*
  Copyright (c) 2019-2022, Michael Gummere.
  All rights reserved.

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated and is required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
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
	// Run Loop
	while (true) {
		/* Steering
		 * Handled by ARMS
		 */
		// clang-format off
		arms::chassis::arcade(
			master.get_analog(ANALOG_LEFT_Y) * (double)100 / 127,
		    master.get_analog(ANALOG_RIGHT_X) * (double)100 / 127,
			true
		);
		if((master.get_analog(ANALOG_LEFT_X) * (double)200 / 127) > 10 || (master.get_analog(ANALOG_LEFT_X) * (double)200 / 127) < -10) {
			hMtr.moveVelocity(master.get_analog(ANALOG_LEFT_X) * (double)200 / 127);
		} else {
			hMtr.moveVelocity(0);
		}
		// clang-format on

		/* Autonomous Manual Trigger
		 * If the robot is not connected to competition control
		 * and the button is pressed, the robot will the autonomous
		 * routine to allow for easy testing.
		 */
		if (master.get_digital_new_press(DIGITAL_X) && !pros::competition::is_connected())
			autonomous();

		/* Game Related Subsystems
		 * Controls for game specific functions
		 */
		gameSystemControls();

		/* Brake System
		 * The brake system is a safety feature that prevents the robot from being
		 * punished by other robots. Uses basic logic for toggle button
		 */
		if (master.get_digital_new_press(DIGITAL_B) == 1) {
			pbrake = !pbrake;
		}
		prosBrake(pbrake);

		// Lastly, delay
		pros::delay(2);
	}
}
