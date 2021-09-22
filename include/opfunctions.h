/*
 * Copyright (c) 2019-2021, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef OPFUNC_H_
#define OPFUNC_H_

// Declare drive system variables.
bool pbrake = true;

// Declare driver functions
void tankDrive();
void arcadeDrive();
void customBrake(bool pbrake);
void prosBrake(bool pbrake);

#endif
