/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "main.h"

// int settle_count;
// int settle_time;
// double settle_threshold_linear;
// double settle_threshold_angular;

// AUTO LIFT FUNCTIONS
// namespace deFenestration::lift {
// int wheelMoving(double sv, double* psv) {
// 	int isMoving = 0;
// 	double thresh = settle_threshold_linear;

// 	if (fabs(sv - *psv) > thresh)
// 		isMoving = 1;

// 	*psv = sv;

// 	return isMoving;
// }

// bool settled() {
// 	static double psv_left = 0;
// 	static double psv_right = 0;
// 	static double psv_middle = 0;

// 	int wheelMovingCount = 0;

// 	wheelMovingCount += wheelMoving(liftMotors.getPosition(), &psv_left);

// 	if (wheelMovingCount == 0)
// 		settle_count++;
// 	else
// 		settle_count = 0;

// 	// not driving if we haven't moved
// 	if (settle_count > settle_time)
// 		return true;
// 	else
// 		return false;
// }

// void waitUntilSettled() {
// 	while (!settled()) pros::delay(10);
// }

// void resetLift() {
// 	liftMotors.moveVelocity(-100);
// 	waitUntilSettled();
// 	liftMotors.moveRelative(30, 100);
// 	waitUntilSettled();
// 	liftMotors.tarePosition();
// }
// } // namespace deFenestration::lift

// AUTO CLAW FUNCTIONS
// bool clawState = true;
// namespace deFenestration::claw {

// void toggleClaw() {
// 	if (clawState == false) {
// 		// If the claw is open, close it
// 		clawP.set_value(true);
// 		clawState = true;
// 	} else {
// 		// If the claw is closed, open it
// 		clawP.set_value(false);
// 		clawState = false;
// 	}
// 	pros::delay(210);
// }

// void puncher() {
// 	// Punch out rings
// 	AWP.set_value(true);
// 	pros::delay(1000);
// 	// Retract the puncher
// 	AWP.set_value(false);
// }
// } // namespace deFenestration::claw

bool initialized = false;
namespace deFenestration::vision {} // namespace deFenestration::vision
