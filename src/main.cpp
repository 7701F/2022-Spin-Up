/**
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "main.h"

int arm_speed = 60;
int claw_speed = 30;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
// void on_center_button() {
// 	static bool pressed = false;
// 	pressed = !pressed;
// 	if (pressed) {
// 		pros::lcd::set_text(2, "I was pressed!");
// 	} else {
// 		pros::lcd::clear_line(2);
// 	}
// }

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// pros::lcd::initialize();
	
	// pros::lcd::print(0, "       .---.");
	// pros::lcd::print(1, "      /     \\");
	// pros::lcd::print(2, "      \\.@-@./");
	// pros::lcd::print(3, "      /`\\_/`\\");
	// pros::lcd::print(4, "     //  _  \\");
	// pros::lcd::print(5, "    | \\     )|_");
	// pros::lcd::print(6, "   /`\\_`>  <_/ \\");
	// pros::lcd::print(7, "   \\__/'---'\\__/");

	display();

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	return;
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
	return;
}

void autonomous() {

	// Templates
	// drive(60,100,1000);
	// turn(-360,100,1000);
	// lift(-180,100,1000);
	// grab(-60,100,1000);

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
		/* TODO: rewrite this as part of the LVGL conversion
		pros::lcd::print(0, "%d %d    .---.", (master.get_analog(ANALOG_LEFT_X)) >> 1, 
			(master.get_analog(ANALOG_LEFT_Y)) >> 0);
		*/

		// Arcade Steering
		// Get analog stick values
		int forward_backward = master.get_analog(ANALOG_LEFT_Y);
		int left_right = master.get_analog(ANALOG_LEFT_X);
		// Move the motors
		left_mtr.move(forward_backward + left_right);
		right_mtr.move(forward_backward - left_right);

		// Arm Control
		if(master.get_digital(DIGITAL_L2)) {
			// Move down?
			arm_mtr.move_velocity(arm_speed);
			arm1_mtr.move_velocity(-arm_speed);
		}
		else if (master.get_digital(DIGITAL_L1)) {
			// Move up?
			arm_mtr.move_velocity(-arm_speed);
			arm1_mtr.move_velocity(arm_speed);
		}
		else {
			// Zero out arm motors
			arm_mtr.move_velocity(0);
			arm1_mtr.move_velocity(0);
		}

		// Grab Control
		if(master.get_digital(DIGITAL_R1)) {
			// Move motor down when R1 is pressed
			claw_mtr.move_velocity(-claw_speed);
		}
		else if (master.get_digital(DIGITAL_R2)) {
			// Move motor up when R2 is pressed
			claw_mtr.move_velocity(claw_speed);
		}
		else {
			// If not accelerating or decellerating, zero the motor
			claw_mtr.move_velocity(0);
		}

		// Old strafe code, not needed for new robot but kept for posterity
		// Strafe
		// if(master.get_digital(DIGITAL_A)){
		// 	right_mtr.move_velocity(-127);
		// 	left_mtr.move_velocity(127);
		// 	r_right_mtr.move_velocity(127);
		// 	r_left_mtr.move_velocity(-127);
		// }
		// else if (master.get_digital(DIGITAL_Y)){
		// 	right_mtr.move_velocity(127);
		// 	left_mtr.move_velocity(-127);
		// 	r_right_mtr.move_velocity(-127);
		// 	r_left_mtr.move_velocity(127);
		// }
		// else{
		// 	// right_mtr.move_velocity(0);
		// 	// left_mtr.move_velocity(0);
		// 	// r_right_mtr.move_velocity(0);
		// 	// r_left_mtr.move_velocity(0);
		// }

		// Lastly, delay
		pros::delay(20);

	}
}
