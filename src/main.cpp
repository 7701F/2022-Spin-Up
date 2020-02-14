/**
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "main.h"

// int intake_speed = 172;
int angler_speed = 60;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
*/
void initialize() {

	display();

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
*/
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
*/
void competition_initialize() {}

void autonomous() {

	/* Templates
		drive(60,100,1000);
	 	turn(-360,100,1000);
		lift(-180,100,1000);
		grab(-60,100,1000);
	*/

	drive(34, 100, 1000);
	drive(-34,-100, 1000);

}


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
void opcontrol() {
	
	// Controller
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	
	// Run Loop
	while (true) {

		// Arcade Steering
		int forward_backward = master.get_analog(ANALOG_LEFT_Y);
		int left_right = master.get_analog(ANALOG_LEFT_X);

		// Intake Stick
		int intake_speed = master.get_analog(ANALOG_RIGHT_Y);

		// Move the motors
		left_mtr.move(forward_backward + left_right);
		right_mtr.move(forward_backward - left_right);

		// Arm Control
		if(true) {
			// Move intakes
			intake_mtr.move_velocity(-master.get_analog(ANALOG_RIGHT_Y));
			intake1_mtr.move_velocity(master.get_analog(ANALOG_RIGHT_Y));
		}  else {
			// Zero out intake motors
			intake_mtr.move_velocity(1);
			intake1_mtr.move_velocity(1);
		}

		// Angle Control
		if(master.get_digital(DIGITAL_R1)) {
			// Move motor down when R1 is pressed
			angler_mtr.move_velocity(-angler_speed);
		}
		else if (master.get_digital(DIGITAL_R2)) {
			// Move motor up when R2 is pressed
			angler_mtr.move_velocity(angler_speed);
		}
		else {
			// If not accelerating or decellerating, zero the motor
			angler_mtr.move_velocity(0);
		}

		// Lastly, delay
		pros::delay(20);

	}
}
