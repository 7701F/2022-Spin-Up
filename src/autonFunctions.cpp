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
     in a product, an acknowledgment in the product documentation would be
     appreciated and is required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
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
namespace deFenestration::vision {

} // namespace deFenestration::vision
