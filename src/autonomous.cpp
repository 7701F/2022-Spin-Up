/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "main.h"

std::int32_t mmToInch() {
	return (distanceR.get() / 25.4) + 4;
}

/* Test
 */
void turnImuPID(int turnToHeading, double power) {
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
	/*/////////////////////////////////////////////
	NOTE:
	Error is a float declared at global level, it represents the difference between target
	velocity and current velocity

	power is a float declared at global level, it represents target velocity

	velocity is a float declared at global level, it is the current measured velocity of the
	shooter wheels
	/////////////////////////////////////////////*/

	// convert from absolute to relative set point
	turnToHeading = turnToHeading - (int)arms::chassis::angle() % 360;

	// make sure all turns take most efficient route
	if (turnToHeading > 180)
		turnToHeading -= 360;
	else if (turnToHeading < -180)
		turnToHeading += 360;

	while (imu_sensor.get_heading() != turnToHeading) {
		double velocity =
		    (arms::chassis::rightMotors->getActualVelocity() + arms::chassis::leftMotors->getActualVelocity()) /
		    2;
		float error = power - velocity; // calculates difference between current velocity and target velocity

		if (error < integralActiveZone && error != 0) // total error only accumulates where /
		                                              // //there is error, and when the error
		                                              // is within the integral active zone
		{
			errorT += error; // adds error to the total each time through the loop
		} else {
			errorT = 0; // if error = zero or error is not withing the active zone, total /
			            // //error is set to zero
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

		arms::chassis::rightMotors->moveVoltage(current);
		arms::chassis::leftMotors->moveVoltage(-current);

		pros::delay(20); // waits so we dont hog all our CPU power or cause loop instability
	}
}

// Right win point
void Rauton() {
	deFenestration::claw::toggleClaw();
	arms::chassis::move(20, 80);
	deFenestration::claw::toggleClaw();
	liftMotors.moveRelative(30, 100);
	pros::delay(300);
	arms::chassis::turnAsync(-60, 80);
	arms::chassis::move(-20, 80);
	deFenestration::claw::toggleClaw();
	pros::delay(30);
}

// Yellow goal
void Yauton() {
	deFenestration::claw::toggleClaw();
	arms::chassis::move(64, 100);
	deFenestration::claw::toggleClaw();
	pros::delay(250);
	arms::chassis::move(-50, 100);
	deFenestration::claw::toggleClaw();
}

// Left win point
void Lauton() {
	// deFenestration::claw::puncher();
	// arms::chassis::turn(90, 80);
	arms::chassis::move(5, 50);
	deFenestration::claw::toggleClaw();
	arms::chassis::move(-15, 80);
	pros::delay(500);
	arms::chassis::move(-6, 80);
	arms::chassis::turn(-80, 60);
	arms::chassis::move(60, 100);
	arms::chassis::moveAsync(5, 75);
	deFenestration::claw::toggleClaw();
	pros::delay(300);
	liftMotors.moveRelative(30, 75);
	pros::delay(500);
	arms::chassis::move(-60, 100);
}

/*
// Programming Skills
void Sauton() {
  winchM.move_relative(-2065, -100);
  pros::delay(3250);
  arms::chassis::move(-30, 50);
  winchM.move_relative(1100, 100);
  pros::delay(1250);
  arms::chassis::move(28, 60);
  arms::chassis::turn(150, 50);
  arms::chassis::move(80, 80);
  deFenestration::claw::toggleClaw();
  pros::delay(850);
  arms::chassis::move(-80, 80);
  arms::chassis::turn(45, 50);
  deFenestration::claw::toggleClaw();
  pros::delay(300);
  arms::chassis::turn(-85, 50);
  arms::chassis::move(65, 80);
  arms::chassis::move(50, 80);
}

// Programming Skills 2.0
void Sauton2() {
  // Fetch blue start MOGO
  arms::chassis::move(8, 50);
  // arms::chassis::turnAbsolute(180, 50);
  // winchM.move_relative(-2065, -100);
  // pros::delay(3250);
  // arms::chassis::move(dist * -1, 50);
  // winchM.move_relative(1100, 100);
  // pros::delay(1400);
  arms::chassis::move(70, 80);
  // Move forward to turn
  arms::chassis::move(-25, 50);
  arms::chassis::turn(-90, 50);
  // Turn to face yellow right MOGO
  arms::chassis::move(25, 100);
  // Grab yellow right MOGO
  deFenestration::claw::toggleClaw();
  arms::chassis::turn(90, 50);
  arms::chassis::move(15, 80);
  arms::chassis::turn(-90, 50);
  liftMotors.moveRelative(380, 100);
  arms::chassis::move(10, 80);
  arms::chassis::turnAbsolute(0);
  arms::chassis::move(10);
  // Place yellow MOGO on balance board
  deFenestration::claw::toggleClaw();
  // Move back to face yellow middle MOGO
  arms::chassis::move(-10, 10);
  arms::chassis::turnAsync(180, 50);
  liftMotors.moveRelative(-380, -100);
  deFenestration::lift::waitUntilSettled();
  arms::chassis::move(50, 50);
  // Grab yellow middle MOGO
  deFenestration::claw::toggleClaw();
  // Turn around to face the balance board
  arms::chassis::move(4, 50);
  arms::chassis::turnAbsolute(0, 50);
  arms::chassis::moveAsync(60, 80);
  liftMotors.moveRelative(380, 80);
  deFenestration::lift::waitUntilSettled();
  arms::chassis::move(10, 50);
  // Drop the mogo and move back to face the balance board
  deFenestration::claw::toggleClaw();
  // Move back to face the yellow left MOGO
  arms::chassis::move(-10, 50);
  arms::chassis::turn(-180, 50);
  arms::chassis::move(20, 80);
  liftMotors.moveRelative(-380, -80);
  deFenestration::lift::waitUntilSettled();
  arms::chassis::move(10, 50);
  liftMotors.moveAbsolute(3, -80);
  deFenestration::lift::waitUntilSettled();
  arms::chassis::move(30, 80);
  arms::chassis::turnAbsolute(90, 50);
  // Grab the yellow left MOGO
  deFenestration::claw::toggleClaw();
  // Turn torwards the balance board
  arms::chassis::turnAbsolute(90, 50);
  // Drive to it
  arms::chassis::move(30, 80);
  // Get to the right spot on the balance board
  arms::chassis::turnAbsolute(90, 80);
  arms::chassis::move(20, 80);
  arms::chassis::turnAbsolute(-90, 80);
  // Put up lift
  liftMotors.moveRelative(380, 80);
  deFenestration::lift::waitUntilSettled();
  arms::chassis::move(10, 50);
  // Drop the MOGO
  deFenestration::claw::toggleClaw();
  // Move back
  arms::chassis::move(-30, 80);
  liftMotors.moveAbsolute(3, 80);
  deFenestration::lift::waitUntilSettled();
  // Turn to face the red MOGO
  arms::chassis::turnAbsolute(-90, 50);
  // vision::redLocate();
  arms::chassis::move(10, 80);
  arms::chassis::turnAbsolute(-30, 50);
  arms::chassis::move(50, 80);
  // Grab it
  deFenestration::claw::toggleClaw();
  arms::chassis::move(-10, 50);
  arms::chassis::turnAbsolute(-15, 50);
  // Move it to the red side
  arms::chassis::move(50, 80);
  // Drop it
  deFenestration::claw::toggleClaw();
  // Move back to our side
  arms::chassis::move(-70, 100);
}

// Programming Skills 3.0
void Sauton3() {
  arms::odom::init();
  arms::odom::reset();
  arms::chassis::resetAngle(180);
  winchM.move_relative(-2065, -100);
  pros::delay(3250);
  arms::chassis::move(-78, 50);
  winchM.move_relative(1100, 100);
  pros::delay(1400);
  arms::chassis::turn(90, 50);
  ringTask = pros::Task(ringPID);
  arms::chassis::move(50);
  pros::Task(ringTask).remove();
  ringTask = (pros::task_t)NULL;
  arms::chassis::move(30);
  deFenestration::claw::toggleClaw();
  arms::chassis::turn(-90);
  arms::chassis::move(96);
}
*/

// Programming Skills 4.0
void Sauton4() {
	// Prime Claw
	deFenestration::claw::toggleClaw();

	// First Push
	arms::chassis::move(93, 100);
	deFenestration::claw::toggleClaw();

	// Turn to first yellow and push
	arms::chassis::turn(-135, 50);
	liftMotors.moveAbsolute(280, 80);
	arms::chassis::move(93, 80);

	// Stack it
	while (mmToInch() > 0) {
		arms::chassis::rightMotors->moveVelocity(80);
		arms::chassis::leftMotors->moveVelocity(80);
	}
	deFenestration::claw::toggleClaw();
	arms::chassis::rightMotors->moveVelocity(0);
	arms::chassis::leftMotors->moveVelocity(0);

	// Move back
	arms::chassis::move(-5, 80);
	liftMotors.moveAbsolute(5, 80);

	// Turn around
	// arms::chassis::turn(135, 50);
	arms::chassis::turnAbsolute(0);

	// Push it
	arms::chassis::move(50, 80);
	deFenestration::claw::toggleClaw();
	pros::delay(100);
	arms::chassis::move(43, 80);
	liftMotors.moveAbsolute(280, 80);
	// arms::chassis::move(93, 80);

	// Stack big yellow
	while (mmToInch() > 0) {
		arms::chassis::rightMotors->moveVelocity(80);
		arms::chassis::leftMotors->moveVelocity(80);
	}
	deFenestration::claw::toggleClaw();
	arms::chassis::rightMotors->moveVelocity(0);
	arms::chassis::leftMotors->moveVelocity(0);

	// Move back
	arms::chassis::move(-5, 80);
	// Turn around
	arms::chassis::turn(-135, 50);
	liftMotors.moveAbsolute(5, 80);

	//  Push yellow
	arms::chassis::move(93, 80);

	arms::chassis::turn(135, 50);

	arms::chassis::move(93, 80);

	arms::chassis::turnAbsolute(0);

	arms::chassis::move(66);
	pros::delay(100);
	deFenestration::claw::toggleClaw();
	pros::delay(100);

	arms::chassis::move(-115);
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	arms::chassis::resetAngle();
	arms::pid::init();

	// Auton Selector Logic
	switch (arms::selector::auton) {
		case -4:
			break;
		case -3:
			break;
		case -2:
			deFenestration::vision::alignRobot(2);
			break;
		case -1:
			arms::chassis::move(65, 80);
			arms::chassis::moveAsync(10);
			deFenestration::claw::toggleClaw();
			pros::delay(250);
			arms::chassis::move(-50, 100);
			break;
		case 0:
			Sauton4();
			break;
		case 1:
			Yauton();
			break;
		case 2:
			Rauton();
			break;
		case 3:
			Lauton();
			break;
		case 4:
			break;
		default:
			break;
	}

	printf("Successfully ran auton: %d\n", arms::selector::auton);
}
