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

// AUTO FUNCTIONS
namespace arms::lift {
int wheelMoving(double sv, double* psv);

bool settled();

void waitUntilSettled();

void resetLift();
} // namespace arms::lift

#endif
