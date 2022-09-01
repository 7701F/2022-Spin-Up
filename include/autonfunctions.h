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
