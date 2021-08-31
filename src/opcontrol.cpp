/**
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "main.h"

bool pbrake = true;
/**
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
void opcontrol()
{

	// Controller
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	// Run Loop
	while (true)
	{

		/* // Arcade Steering
			int forward_backward = master.get_analog(ANALOG_LEFT_Y);
			int left_right = master.get_analog(ANALOG_LEFT_X);
			leftMtr.move(forward_backward + left_right);
			rightMtr.move(forward_backward - left_right);
		*/

		// Move the steering motors
		leftMtr.move(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X));
		rightMtr.move(master.get_analog(ANALOG_RIGHT_Y) + master.get_analog(ANALOG_RIGHT_Y));
		leftMtrR.move(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X));
		rightMtrR.move(master.get_analog(ANALOG_RIGHT_Y) + master.get_analog(ANALOG_RIGHT_Y));

		//
		if (master.get_digital(DIGITAL_A) == 1)
		{
			pbrake = true;
		}

		if (master.get_digital(DIGITAL_B) == 1)
		{
			pbrake = false;
		}

		if (pbrake == true)
		{
			leftMtr.move(20);
			rightMtr.move(20);
			leftMtrR.move(-20);
			rightMtrR.move(-20);
		}

		// if (pbrake == false)
		// {
		// 	leftMtr.move(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X));
		// 	rightMtr.move(master.get_analog(ANALOG_RIGHT_Y) + master.get_analog(ANALOG_RIGHT_Y));
		// 	leftMtrR.move(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X));
		// 	rightMtrR.move(master.get_analog(ANALOG_RIGHT_Y) + master.get_analog(ANALOG_RIGHT_Y));
		// }

		// Lastly, delay
		pros::delay(1);
	}
}
