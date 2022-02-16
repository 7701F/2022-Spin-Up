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
namespace arms::lift {
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
	while (!settled()) pros::delay(1);
}

void resetLift() {
	liftMotors.moveVelocity(-100);
	waitUntilSettled();
	liftMotors.moveRelative(30, 100);
	waitUntilSettled();
	liftMotors.tarePosition();
}
} // namespace arms::lift

int csettle_count;
int csettle_time;
double csettle_threshold_linear;
double csettle_threshold_angular;

// AUTO CLAW FUNCTIONS
bool clawState = false;
namespace arms::claw {
int wheelMoving(double sv, double* psv) {
	int isMoving = 0;
	double thresh = csettle_threshold_linear;

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

	wheelMovingCount += wheelMoving(clawM.get_position(), &psv_left);

	if (wheelMovingCount == 0)
		csettle_count++;
	else
		csettle_count = 0;

	// not driving if we haven't moved
	if (csettle_count > csettle_time)
		return true;
	else
		return false;
}

void waitUntilSettled() {
	while (!settled()) pros::delay(1);
}

void toggleClaw(bool drop) {
	if (clawP.)
		clawM.move_absolute(0, 80);
	else
		clawM.move_absolute(210, 80);
	waitUntilSettled();
}

void puncher (bool clamp) {
	AWP.set_value(true);
	pros::delay(200);
	AWP.set_value(false);
}
} // namespace arms::claw

// pros::vision_signature_s_t RED_SIG = pros::Vision::signature_from_utility(
//     1, 8973, 11143, 10058, -2119, -1053, -1586, 5.4, 0);

namespace vision {} // namespace vision
