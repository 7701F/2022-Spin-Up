#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.

 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

// OPControl Function
void opcontrol() {

	// Controller
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	// Variables
	int arm_speed = 45;
	int claw_speed = 45;

	// Run Loop
	while (true) {
		// %d %d %d
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

		// Arcade Steering
		int forward_backward = master.get_analog(ANALOG_LEFT_Y);
		int left_right = master.get_analog(ANALOG_LEFT_X);
		left_mtr.move(forward_backward + left_right);
		r_left_mtr.move(forward_backward + left_right);
		right_mtr.move(forward_backward - left_right);
		r_right_mtr.move(forward_backward - left_right);

		// Arm Control
		if(master.get_digital(DIGITAL_L2)){
			arm_mtr.move_velocity(arm_speed);
		}
		else if (master.get_digital(DIGITAL_L1)){
			arm_mtr.move_velocity(-arm_speed);
		}
		else{
			arm_mtr.move_velocity(0);
		}

		// Claw Control
		if(master.get_digital(DIGITAL_R1)){
			claw_mtr.move_velocity(-claw_speed);
		}
		else if (master.get_digital(DIGITAL_R2)){
			claw_mtr.move_velocity(claw_speed);
		}
		else{
			claw_mtr.move_velocity(0);
		}

		// Strafe
		if(master.get_digital(DIGITAL_A)){
			right_mtr.move_velocity(-100);
			left_mtr.move_velocity(100);
			r_right_mtr.move_velocity(100);
			r_left_mtr.move_velocity(-100);
		}
		else if (master.get_digital(DIGITAL_Y)){
			right_mtr.move_velocity(100);
			left_mtr.move_velocity(-100);
			r_right_mtr.move_velocity(-100);
			r_left_mtr.move_velocity(100);
		}
		else{
			// right_mtr.move_velocity(0);
			// left_mtr.move_velocity(0);
			// r_right_mtr.move_velocity(0);
			// r_left_mtr.move_velocity(0);
		}

		pros::delay(20);

	}
}
