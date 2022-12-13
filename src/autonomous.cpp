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
#include "ARMS/flags.h"

/* Util Functions */
namespace COLORS {
const int BLUE = 1;
const int RED = 2;
const int ERROR = 3;
} // namespace COLORS

/* Gets the # of Frisbees in the Indexer */
int getFrisbeesInIndexer() {
	int sensorDistance = distanceFilter.filter(indexerSensor.get());
	if (sensorDistance > 105) {
		return 0;
	} else if (sensorDistance > 90) {
		return 1;
	} else if (sensorDistance > 70) {
		return 2;
	} else {
		return 3;
	}
}

/* Get the color of the Roller from the Optical Sensor */
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

/* Set Roller to Red */
void setRollerRed() {
	int rollerStartTime = pros::millis();
	roller.move_velocity(100);
	while (getRollerColor() != 1 && pros::millis() - rollerStartTime < 1500) {
		pros::delay(10);
	}
	pros::delay(200);
	roller.move_velocity(0);
}

/* Set Roller to Blue */
void setRollerBlue() {
	int rollerStartTime = pros::millis();
	roller.move_velocity(100);
	while (getRollerColor() != 2 && pros::millis() - rollerStartTime < 1500) {
		pros::delay(10);
	}
	pros::delay(200);
	roller.move_velocity(0);
}

/* Blue Back Auton */
void backAuto(int color) {
	using namespace arms::chassis;

	move(6);
	turn(-30);
	move(-10, arms::REVERSE);
	move(-10, -100, arms::REVERSE | arms::ASYNC);
	if (color == 1)
		setRollerBlue();
	if (color == 2)
		setRollerRed();
}

/* Short Side Auton */
void shortAuto(int color) {
	using namespace arms::chassis;

	move(100, arms::ASYNC);
	while (!settled()) {
		pros::delay(10);
	}
	conveyor.move_velocity(100);
	pros::delay(250);
	conveyor.move_velocity(0);
	// if (color == 1)
	// 	setRollerBlue();
	// if (color == 2)
	// 	setRollerRed();
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
	/* Auton Selector Logic */
	// Negative = Blue
	// Positive = Red
	switch (arms::selector::auton) {
		case -3:
			// Do Nothing.
			break;
		case -2:
			// backAuto(COLORS::BLUE);
			break;
		case -1:
			shortAuto(COLORS::BLUE);
			break;
		case 0:
			break;
		case 1:
			shortAuto(COLORS::RED);
			break;
		case 2:
			// backAuto(COLORS::RED);
			break;
		case 3:
			// Do Nothing.
			break;
		default:
			break;
	}

	printf("Successfully ran auton: %d\n", arms::selector::auton);
}
