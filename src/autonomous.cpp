/*
  Copyright (c) 2019-2022 7701F

  This software is provided 'as-is', without any express or implied warranty. In no event will
  the authors be held liable for any damages arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose, including commercial
  applications, and to alter it and redistribute it freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you wrote the
  original software. If you use this software in a product, an acknowledgment (see the following)
  in the product documentation is required.

  Portions Copyright (c) 2019-2022 7701F

  2. Altered source versions must be plainly marked as such, and must not be misrepresented as
  being the original software.

  3. This notice may not be removed or altered from any source distribution.
*/
#include "7701.h"
#include "main.h"
#include "sylib/sylib.hpp"

/* Util Functions */
int getFrisbeesInIntake() {
	int sensorDistance = distanceFilter.filter(indexerSensor.get());
	if (sensorDistance > 100) {
		return 0;
	} else if (sensorDistance > 55) {
		return 1;
	} else if (sensorDistance > 35) {
		return 2;
	} else {
		return 3;
	}
}

int getRollerColor() {
	if (rollerSensor.get_proximity() < 200) {
		return 0;
	}

	double hue = hueFilter.filter(rollerSensor.get_hue());
	if (hue < 260 && hue > 230) {
		return 1; // blue
	} else if (hue < 30 && hue > 0) {
		return 2; // red
	} else {
		return 3; // lol it doesnt know
	}
	return 0;
}

void setRollerRed() {
	int rollerStartTime = pros::millis();
	roller.moveVelocity(100);
	while (getRollerColor() != 2 && pros::millis() - rollerStartTime < 1500) {
		pros::delay(10);
	}
	roller.moveVelocity(0);
	pros::delay(50);
	rollerStartTime = pros::millis();
	roller.moveVelocity(100);
	while (getRollerColor() != 1 && pros::millis() - rollerStartTime < 1500) {
		pros::delay(10);
	}
	roller.moveVelocity(50);
	pros::delay(250);
	roller.moveVelocity(0);
}

void setRollerBlue() {
	int rollerStartTime = pros::millis();
	roller.moveVelocity(100);
	while (getRollerColor() != 1 && pros::millis() - rollerStartTime < 1500) {
		pros::delay(10);
	}
	roller.moveVelocity(0);
	pros::delay(50);
	rollerStartTime = pros::millis();
	roller.moveVelocity(100);
	while (getRollerColor() != 2 && pros::millis() - rollerStartTime < 1500) {
		pros::delay(10);
	}
	roller.moveVelocity(50);
	pros::delay(250);
	roller.moveVelocity(0);
}

/*
 * Autonomous 1
 */
void redFront() {
	using namespace arms::chassis;
	arms::odom::reset({{0, 24}});

	turn({0, 24}, 75);
	move({{0, 24}}, 200);
	setRollerRed();
}

/*
 * Autonomous 2
 */
void redBack() {
	using namespace arms::chassis;
	arms::odom::reset({{0, 24}});

	turn({0, 24}, 75);
	move({{0, 24}}, 200);
}

/* Programming Skills */
void Sauton() {
	deFenestration::Flywheel::FwVelocitySet(96, 0.2);

	using namespace arms::chassis;
	arms::odom::reset({{0, 24}});

	turn({0, 24}, 75);
	move({{0, 24}}, 200);
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
	deFenestration::IMU imus;

	/* Auton Selector Logic */
	switch (arms::selector::auton) {
		case -3:
			break;
		case -2:
			break;
		case -1:
			break;
		case 0:
			Sauton();
			break;
		case 1:
			// redFront();
			break;
		case 2:
			redBack();
			break;
		case 3:
			imus.reset();

			imus.turnToH(90, 100);

			master.print(2, 0, "%f", imus.status());
			break;
		default:
			break;
	}

	printf("Successfully ran auton: %d\n", arms::selector::auton);
}
