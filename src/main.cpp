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
      in a product, an acknowledgment in the product documentation is required. Your compliance is appreciated.
  2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "main.h"
#include "7701.h"

#include <sstream>

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	/* ARMS & Controller initialization */
	arms::init();

	/* Controller Status Display */
	pros::Task controllerTask{[=] {
		master.clear();
		master.print(2, 0, "Starting 7701F.");
		pros::delay(50);
		master.print(2, 0, "Starting 7701F..");
		pros::delay(50);
		master.print(2, 0, "Starting 7701F... Ready!");
		pros::delay(100);
		master.print(2, 0, "Running...              ");
		pros::delay(500);

		/**
		 * Only print every 50ms, the controller text update rate is slow.
		 * Any input faster than this will be dropped.
		 */
		int count;
		while (true) {
			if (count == 100) {
				std::stringstream autonstr;
				autonstr << "Auton: " << arms::selector::auton << "\r";
				master.print(0, 0, autonstr.str().c_str());
			} else if (count == 50) {
				std::stringstream brakestr;
				brakestr << "Brake: " << (pbrake ? "ON" : "OFF") << "\r";
				master.print(1, 0, brakestr.str().c_str());
			}

			count++;
			count %= 200;
			pros::delay(1);
		}
	}};
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	static int count = 1;
	printf("Disabled called %d\n", count++);

	while (true) {
		pros::delay(1000);
	}
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	static int count = 1;
	printf("Comp Init called %d\n", count++);
}
