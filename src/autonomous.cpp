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

bool initialized = false;
auto shirt = pros::Vision::signature_from_utility(1, 7695, 9019, 8357, -4133, -2679, -3406, 3.000, 0);
auto disk = pros::Vision::signature_from_utility(2, 7657, 8273, 7966, -2251, -1733, -1992, 3.000, 0);
auto card = pros::Vision::signature_from_utility(3, -129, 417, 144, -4459, -3907, -4182, 3.000, 0);

pros::Vision vision_sensor = pros::Vision(7);

/* Color Signatures */
auto test_sig = 1;
namespace deFenestration::Vision {
/*
 * Initialize Vision Sensor
 */
void init() {
	if (initialized) {
		return;
	}

	/* Set Color Signatures */

	/* Set Objects */

	initialized = true;
}

/*
 * Distance Logic
 */
int32_t mmToInch() {
	int32_t x = (distance_sensor.get() / 25.4) + 4;
	return x;
}
} // namespace deFenestration::Vision

/*
 * Autonomous 1
 */
void redFront() {
	deFenestration::Flywheel::FwVelocitySet(96, 0.2);

	using namespace arms::chassis;
	arms::odom::reset({{0, 24}});
	turn({0, 24}, 75);
	move({{0, 24}}, 200);

	// move(24, 100, arms::RELATIVE);

	// turn({24, 24}, 75);

	// move({{24, 0}}, 50, arms::THRU | arms::ASYNC);
}

/* Programming Skills */
void Sauton() {
	deFenestration::Flywheel::FwVelocitySet(96, 0.2);

	using namespace arms::chassis;
	arms::odom::reset({{0, 24}});

	// move(24, 100, arms::RELATIVE);

	turn({24, 24}, 75);

	// move({{24, 0}}, 50, arms::THRU | arms::ASYNC);
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
			break;
		case 3:
			break;
		default:
			break;
	}

	printf("Successfully ran auton: %d\n", arms::selector::auton);
}
