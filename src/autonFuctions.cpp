/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "main.h"

int settle_count;
int settle_time;
double settle_threshold_linear;
double settle_threshold_angular;

// AUTO LIFT FUNCTIONS
namespace deFenestration::lift {
int wheelMoving(double sv, double* psv) {
	int isMoving = 0;
	double thresh = settle_threshold_linear;

	if (fabs(sv - *psv) > thresh)
		isMoving = 1;

	*psv = sv;

	return isMoving;
}

bool settled() {
	static double psv_left = 0;
	static double psv_right = 0;
	static double psv_middle = 0;

	int wheelMovingCount = 0;

	wheelMovingCount += wheelMoving(liftMotors.getPosition(), &psv_left);

	if (wheelMovingCount == 0)
		settle_count++;
	else
		settle_count = 0;

	// not driving if we haven't moved
	if (settle_count > settle_time)
		return true;
	else
		return false;
}

void waitUntilSettled() {
	while (!settled()) pros::delay(10);
}

void resetLift() {
	liftMotors.moveVelocity(-100);
	waitUntilSettled();
	liftMotors.moveRelative(30, 100);
	waitUntilSettled();
	liftMotors.tarePosition();
}
} // namespace deFenestration::lift

// AUTO CLAW FUNCTIONS
bool clawState = false;
namespace deFenestration::claw {

void toggleClaw() {
	if (clawState == false) {
		// If the claw is open, close it
		clawP.set_value(true);
		clawState = true;
	} else {
		// If the claw is closed, open it
		clawP.set_value(false);
		clawState = false;
	}
	pros::delay(210);
}

void puncher() {
	// Punch out rings
	AWP.set_value(true);
	pros::delay(1000);
	// Retract the puncher
	AWP.set_value(false);
}
} // namespace deFenestration::claw

// Signitures
// pros::vision_signature_s_t RED_SIG =
//     pros::Vision::signature_from_utility(1, 6255, 7309, 6782, -325, 223, -52, 3.000, 0);
// pros::vision_signature_s_t YLW_SIG =
//     pros::Vision::signature_from_utility(2, 351, 1099, 724, -3479, -2631, -3054, 3.000, 0);
// pros::vision_signature_s_t BLU_SIG =
//     pros::Vision::signature_from_utility(3, -3073, -2047, -2560, 7899, 12545, 10222, 3.000, 0);

bool initialized = false;
namespace deFenestration::vision {
void init() {
	vision_sensor.set_signature(1, &BLU_SIG);
	vision_sensor.set_signature(2, &RED_SIG);
	vision_sensor.set_signature(3, &YLW_SIG);

	initialized = true;
}

int alignRobot(int color) {
	if (initialized == false) {
		init();
	}
	bool aligned = false;
	vision_sensor.clear_led();

	// Get the position of the goal
	if (vision_sensor.get_object_count() == 0)
		return 0;

	pros::vision_object_s_t goal = vision_sensor.get_by_sig(color, 0);
	printf("%d", goal.x_middle_coord);
	vision_sensor.set_led(32);

	// Align to goal
	while (!aligned) {
		printf("%d", goal.x_middle_coord);
		if (!aligned) {
			arms::chassis::turn(1, 100);
			pros::delay(100);
		} else if (goal.x_middle_coord < 0) {
			arms::chassis::turn(-1, 100);
			pros::delay(100);
		}
		if (goal.x_middle_coord == 0) {
			aligned = true;
		}
	}

	if (aligned == true) {
		return 1;
	} else
		return 0;
}
} // namespace deFenestration::vision
