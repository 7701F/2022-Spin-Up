/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "main.h"

// Honestly my stupidest moment, it stops the robot by driving the motor opposite
// direction of the current velocity.
void customBrake(bool pbrake) {
	if (pbrake == true) {
		if (master.get_analog(ANALOG_LEFT_Y) == 0 && master.get_analog(ANALOG_RIGHT_X) == 0) {
			if (leftMtr.get_actual_velocity() != 0 || rightMtr.get_actual_velocity() != 0 ||
			    leftMtrR.get_actual_velocity() != 0 || rightMtrR.get_actual_velocity() != 0) {
				leftMtr.move_velocity(leftMtr.get_actual_velocity() * -.1);
				rightMtr.move_velocity(rightMtr.get_actual_velocity() * -.1);
				leftMtrR.move_velocity(leftMtrR.get_actual_velocity() * -.1);
				rightMtrR.move_velocity(rightMtrR.get_actual_velocity() * -.1);
			}
		}
	}
}

// Toggles the motor brake mode.
void motorBrake(bool pbrake) {
	if (pbrake == true) {
		if (arms::chassis::leftMotors->getBrakeMode() != okapi::AbstractMotor::brakeMode::hold ||
		    arms::chassis::rightMotors->getBrakeMode() != okapi::AbstractMotor::brakeMode::hold) {
			arms::chassis::setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
			printf("BRAKE TOGGLED: HOLD\n");
		}
	} else if (pbrake == false) {
		if (arms::chassis::leftMotors->getBrakeMode() != okapi::AbstractMotor::brakeMode::coast ||
		    arms::chassis::rightMotors->getBrakeMode() != okapi::AbstractMotor::brakeMode::coast) {
			arms::chassis::setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
			printf("BRAKE TOGGLED: COAST\n");
		}
	}
}

// Ring PID
double power = 600;
void ringPID() {
	float kp = .1;   // proportional konstant
	float ki = .32;  // konstant of integration
	float kd = .026; // konstant of derivation

	float current = 0;            // value to be sent to shooter motors
	float integralActiveZone = 2; // zone of error values in which the total error for the
	                              // integral term accumulates
	float errorT;                 // total error accumulated
	float lastError;              // last error recorded by the controller
	float proportion;             // the proportional term
	float integral;               // the integral term
	float derivative;             // the derivative term
	/*//////////////////////////////////////////////
	NOTE:
	Error is a float declared at global level, it represents the difference between target
	velocity and current velocity

	power is a float declared at global level, it represents target velocity

	velocity is a float declared at global level, it is the current measured velocity of the
	shooter wheels
	/////////////////////////////////////////////*/
	while (true) {
		float error = power - ringM.getActualVelocity(); // calculates difference between current
		                                                 // velocity and target velocity

		if (error < integralActiveZone && error != 0) // total error only accumulates where / there is error, and
		                                              // when the error is within the integral active zone
		{
			errorT += error; // adds error to the total each time through the loop
		} else {
			errorT = 0; // if error = zero or error is not withing the active zone, total / error is set to zero
		}

		if (errorT > 50 / ki) // caps total error at 50
		{
			errorT = 50 / ki;
		}
		if (error == 0) {
			derivative = 0; // if error is zero derivative term is zero
		}
		proportion = error * kp;               // sets proportion term
		integral = errorT * ki;                // sets integral term
		derivative = (error - lastError) * kd; // sets derivative term

		lastError = error; // sets the last error to current error so we can use it in the next loop

		current = proportion + integral + derivative; // sets value current as total of all terms

		ringM.moveVoltage(current); // sets motors to the calculated value

		pros::delay(20); // waits so we dont hog all our CPU power or cause loop instability
	}
}

int liftSpeed;
bool pistonState = false;
bool prevPistonState = false;
bool mogoState = false;
bool ringState = false;
// Combined Claw, Lift, Winch, and Ringlift control function
void gameSystemControls() {
	// Lift Controls
	if (master.get_digital(DIGITAL_L1) == 1) {
		liftSpeed = 127;
	} else if (master.get_digital(DIGITAL_L2) == 1) {
		liftSpeed = -127;
	} else {
		liftSpeed = 0;
	}

	if (fabs(liftSpeed) >= 50 && liftMotors.getPosition() > 0) {
		liftMotors.moveVelocity(liftSpeed * (double)100 / 127);
	} else if (liftSpeed == 0) {
		liftMotors.moveVelocity(0);
	} else if (liftMotors.getPosition() < 0) {
		liftMotors.moveAbsolute(11, 10);
	}

	// Claw Controls
	pistonState = master.get_digital(DIGITAL_R2);
	if (pistonState == true && prevPistonState == false) {
		mogoState = !mogoState;
		clawP.set_value(mogoState);
	}
	prevPistonState = pistonState;

	// Ring Lift Controls
	if (master.get_digital(DIGITAL_R1)) {
		ringState = !ringState;
	}

	if (ringState) {
		ringTask = pros::Task(ringPID);
	} else {
		if (ringTask) {
			pros::Task(ringTask).remove();
			ringTask = (pros::task_t)NULL;
		}
	}

	// Winch Control
	if (master.get_digital(DIGITAL_RIGHT) == 1) {
		winchM.move_velocity(100);
	} else if (master.get_digital(DIGITAL_DOWN) == 1) {
		winchM.move_velocity(-100);
	} else {
		winchM.move_velocity(0);
	}
}
