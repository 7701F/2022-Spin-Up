/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef AUTOFUNC_H_
#define AUTOFUNC_H_

// AUTO LIFT FUNCTIONS
namespace deFenestration::lift {
int wheelMoving(double sv, double* psv);

bool settled();

void waitUntilSettled();

void resetLift();
} // namespace deFenestration::lift

// AUTO CLAW FUNCTIONS
namespace deFenestration::claw {
void toggleClaw();

void puncher();
} // namespace deFenestration::claw

namespace deFenestration::vision {
/** Align the robot to the goal
 * color = 1 for blue, 2 for red, 3 for yellow
 * return 1 if the robot is aligned, 2 if it is not aligned
 * \param color The color code of the goal
 */
int alignRobot(int color);
} // namespace deFenestration::vision

#endif
