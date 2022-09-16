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

bool initialized = false;
visiondetect::Object shirt = visiondetect::Object(
    pros::Vision::signature_from_utility(1, 7695, 9019, 8357, -4133, -2679, -3406, 3.000, 0), 1.05, 5, 31, 50, 0.15);
visiondetect::Object disk = visiondetect::Object(
    pros::Vision::signature_from_utility(1, 7657, 8273, 7966, -2251, -1733, -1992, 3.000, 0), 1.05, 5, 31, 50, 0.15);
visiondetect::Object card = visiondetect::Object(
    pros::Vision::signature_from_utility(2, -129, 417, 144, -4459, -3907, -4182, 3.000, 0), 1.05, 5, 31, 50, 0.15);

/* Distance Logic */
std::int32_t mmToInch() {
	return (distance_sensor.get() / 25.4) + 4;
}

visiondetect::Vision advanced_vision = visiondetect::Vision(7);

/* Color Signatures */
auto test_sig = 1;
namespace deFenestration::auton {
void init() {
	if (initialized) {
		return;
	}

	/* Disable Wi-Fi */
	bool c = pros::competition::is_connected();
	if (c == true)
		advanced_vision.sensor->set_wifi_mode(0);
	else if (c == false)
		advanced_vision.sensor->set_wifi_mode(1);

	initialized = true;
}

void align() {
	if (initialized != true) {
		init();
	}

	visiondetect::detected_object_s_t found;
	found = advanced_vision.detect_object(disk);
	bool turning;
	bool going;

	going = true;
	while (going) {
		while (turning) {
			if (found.x_px > 0) {
				arms::chassis::turn(1, 100);
			} else if (found.x_px < 0) {
				arms::chassis::turn(-1, 100);
			} else if (found.x_px == 0) {
				turning = false;
			}
		}
		if (turning == false) {
			while (mmToInch() >= 4) {
				arms::chassis::move(found.apprx_distance, 100);
			}
			going = false;
		}
	}
}
} // namespace deFenestration::auton

/* Programming Skills */
void Sauton() {
	using namespace arms::chassis;
	arms::odom::reset({{0, 24}});
	move({{24, 0}}, 50, arms::THRU | arms::ASYNC);
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	/* Auton Selector Logic */
	switch (arms::selector::auton) {
		case -3:
			break;
		case -2:
			break;
		case -1:
			break;
		case 0:
			Sauton();
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
	}

	printf("Successfully ran auton: %d\n", arms::selector::auton);
}
