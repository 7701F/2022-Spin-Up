/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "main.h"

// std::int32_t mmToInch() {
// 	return (distanceR.get() / 25.4) + 4;
// }

// Programming Skills
void Sauton() {
	using namespace arms::chassis;
	move({{24, 0}}, 50, arms::THRU | arms::ASYNC);}

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
	arms::pid::init(2.0, 0.04, 0.0, 2.0, 0.04, 0.0, 2.0, 1);

	// Auton Selector Logic
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
