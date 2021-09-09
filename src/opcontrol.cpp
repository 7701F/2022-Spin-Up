/**
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "main.h"
#include "opfunctions.h"

bool pbrake = false;
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

		// Move the steering motors
		tankDrive();

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
			if (leftMtr.get_actual_velocity() != 0)
			{
				leftMtr.move(leftMtr.get_actual_velocity() * -1);
				rightMtr.move(rightMtr.get_actual_velocity() * -1);
				leftMtrR.move(leftMtrR.get_actual_velocity() * -1);
				rightMtrR.move(rightMtrR.get_actual_velocity() * -1);
			}
			// leftMtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			// rightMtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			// leftMtrR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			// rightMtrR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		}

		// if (pbrake == false)
		// {
		// 	// leftMtr.move(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X));
		// 	// rightMtr.move(master.get_analog(ANALOG_RIGHT_Y) + master.get_analog(ANALOG_RIGHT_Y));
		// 	// leftMtrR.move(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X));
		// 	// rightMtrR.move(master.get_analog(ANALOG_RIGHT_Y) + master.get_analog(ANALOG_RIGHT_Y));
		// 	leftMtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		// 	rightMtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		// 	leftMtrR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		// 	rightMtrR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		// }

		// Lastly, delay
		pros::delay(1);
	}
}
