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

pros::task_t matchTimerTask = (pros::task_t)NULL;

// Match Timer Indicator
int matchTimerCount = 105;
void matchTimer() {
	printf("Match Timer: %d\n", matchTimerCount);
	pros::delay(1000);

	while (true) {
		if (matchTimerCount == 1) { // End of match
			master.rumble("----");
			matchTimerCount = 105;
		} else if (matchTimerCount == 35) { // 75 seconds into Driver Control
			master.rumble(".-.-.");
		} else if (matchTimerCount == 60) { // 60 seconds into Driver Control
			master.rumble(". .");
		} else if (matchTimerCount == 75) { // 45 seconds into Driver Control
			master.rumble("-");
		}

		matchTimerCount--;
		printf("Match Timer: %d\n", matchTimerCount);
		pros::delay(1000);
	}
}

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
	// Brake
	// chassis::setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	if (pros::competition::is_connected()) {
		pros::Task matchTimerTask(matchTimer);
	}

	// Run Loop
	while (true) {
		// Steering
		arms::chassis::arcade(
			master.get_analog(ANALOG_LEFT_Y) * (double)100 / 127,
		    master.get_analog(ANALOG_RIGHT_X) * (double)100 /127
		);

		// Game Controls
		gameSystemControls();

		// Brake System
		// Uses basic logic for toggle button
		if (master.get_digital_new_press(DIGITAL_A) == 1) {
			pbrake = !pbrake;
		}
		prosBrake(pbrake);

		if (master.get_digital_new_press(DIGITAL_X) &&
		    !pros::competition::is_connected())
			autonomous();

		// Lastly, delay
		pros::delay(10);
	}
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
	pros::Task controllerTask(ctrlrScr);

	// Set display
	if (!pros::competition::is_connected())
		display();

	// Set brakes on to active bold
	rightLift.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	leftLift.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	clawM.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	winchM.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void killTask() {
	if ( matchTimerTask ) {
		pros::Task(matchTimerTask).remove();
        matchTimerTask = (pros::task_t)NULL;
	}

	// small delay to allow tasks to be removed from run queue
	pros::delay(10);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
    static int count = 1;
    printf("Disabled called %d", count++);

    // kill any tasks we may have started and do not need now
    killTask();

    // disabled is actually a task as well
    // we can either return or block here doing something useful
    // the task will be deleted when driver or auton starts
    while(1) {
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
	arms::selector::init();
}
