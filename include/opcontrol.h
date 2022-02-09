/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef OPCONTROL_H_
#define OPCONTROL_H_

// Task
extern pros::task_t matchTimerTask;

// Kills Match Timer Task
inline void killTask() {
	if (matchTimerTask) {
		pros::Task(matchTimerTask).remove();
		matchTimerTask = (pros::task_t)NULL;
	}

	// small delay to allow tasks to be removed from run queue
	pros::delay(10);
}

// Match Timer Indicator
extern int matchTimerCount;

#endif
