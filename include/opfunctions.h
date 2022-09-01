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

#ifndef OPFUNC_H_
#define OPFUNC_H_

// Declare drive system variables.
inline bool pbrake = true;
inline double speed = 1;

// Declare driver functions
void tankDrive(double speed);
void arcadeDrive();
void customBrake(bool pbrake);
void prosBrake(bool pbrake);
void gameSystemControls();

// Declare Ring PID Task
void ringPID();
inline pros::task_t ringTask = (pros::task_t)NULL;

#endif
