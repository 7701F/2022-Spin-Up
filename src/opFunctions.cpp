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
     in a product, an acknowledgment in the product documentation is required. Your compliance is appreciated.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "main.h"
#include "pros/misc.h"

// Honestly my stupidest moment, it stops the robot by driving the motor opposite direction of the current
// velocity
void customBrake(bool pbrake) {
	if (pbrake == true) {
		if (master.get_analog(ANALOG_LEFT_Y) == 0 && master.get_analog(ANALOG_RIGHT_X) == 0 &&
		    master.get_analog(ANALOG_LEFT_X) == 0) {
			if (leftMotors.getActualVelocity() != 0 || rightMotors.getActualVelocity() != 0) {
				leftMotors.moveVelocity(leftMotors.getActualVelocity() * -2);
				rightMotors.moveVelocity(rightMotors.getActualVelocity() * -2);
				pros::delay(2);
			}
		}
	}
}

// Smart boy motor brake solution
void prosBrake(bool pbrake) {
	if (pbrake == true) {
		if (rightMotors.getBrakeMode() != okapi::AbstractMotor::brakeMode::hold) {
			leftMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
			rightMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

			printf("BRAKE TOGGLED: HOLD\n");
		}
	} else if (pbrake == false) {
		if (rightMotors.getBrakeMode() != okapi::AbstractMotor::brakeMode::coast) {
			leftMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
			rightMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

			printf("BRAKE TOGGLED: COAST\n");
		}
	}
}

void gameSystemControls() {
}
