/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

void drive(double distance, int speed, int wait);
void turn(double degrees, int speed, int wait);
void rotate(double degrees, int speed, int wait);
void eject(double degrees, int speed, int wait);

#endif
