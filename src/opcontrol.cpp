/**
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "main.h"

int angler_speed = 60;
int intake_speed = 175;
bool intake_on = false;

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

    // Move the steering motors
    left_mtr.move(forward_backward + left_right);
    right_mtr.move(forward_backward - left_right);

    // Intake control
    intake_mtr.move_velocity(-master.get_analog(ANALOG_RIGHT_Y));
    intake1_mtr.move_velocity(master.get_analog(ANALOG_RIGHT_Y));

    // Angle Control
    if (master.get_digital(DIGITAL_R1)) {
      // Move motor when R1 is pressed
      angler_mtr.move_absolute(534, -angler_speed);
    } else if (master.get_digital(DIGITAL_R2)) {
      // Move motor when R2 is pressed
      angler_mtr.move_absolute(0, angler_speed);
    } else {
      // If not accelerating or decellerating, zero the motor
      angler_mtr.move_velocity(0);
    }

    // Intake Arm Control
    // if(master.get_digital(DIGITAL_L1)) {
    // 	// Move motor when R1 is pressed
    // 	intakearm_mtr.move_velocity(120);
    // 	intakearm1_mtr.move_velocity(120);
    // }
    // else if (master.get_digital(DIGITAL_L2)) {
    // 	// Move motor when R2 is pressed
    // 	intakearm_mtr.move_velocity(-120);
    // 	intakearm1_mtr.move_velocity(-120);
    // }
    // else {
    // 	// If not accelerating or decellerating, zero the motor
    // 	intakearm_mtr.move_velocity(0);
    // 	intakearm1_mtr.move_velocity(0);
    // }

    // Intake Toggle
    if (master.get_digital(DIGITAL_A) == 1) {
      intake_on = true;
    }

    if (master.get_digital(DIGITAL_B) == 1) {
      intake_on = false;
    }

    if (intake_on == true) {
      intake_mtr.move_velocity(intake_speed);
      intake1_mtr.move_velocity(-intake_speed);
    }

    // Lastly, delay
    pros::delay(20);
  }
}
