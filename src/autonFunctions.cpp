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

#include "ARMS/chassis.h"
#include "main.h"

visiondetect::Vision advanced_vision = visiondetect::Vision(5);

bool initialized = false;
visiondetect::Object shirt = visiondetect::Object(
    pros::Vision::signature_from_utility(1, 7695, 9019, 8357, -4133, -2679, -3406, 3.000, 0), 1.05, 5, 31, 50,
    0.15);

// Signatures
auto test_sig = 1;

std::int32_t mmToInch() {
	float x = distance_sensor.get();
	float y = distance_sensor1.get();
	float val = (x + y) / 2;
	val /= 25.4;
	return val;
}

namespace deFenestration::vision {
void init() {
	if (initialized) {
		return;
	}
	bool c = pros::competition::is_connected();
	if (c == true)
		advanced_vision.sensor->set_wifi_mode(0);
	else if (c == false)
		advanced_vision.sensor->set_wifi_mode(1);

	initialized = true;
}

// void selfDrive() {
// 	bool active = true;
// 	bool going = true;
// 	bool turning = false;
// 	while (active) {
// 		while (going) {
// 			if (mmToInch() > 10) {
// 				if (vision_sensor.get_by_sig(0, test_sig).x_middle_coord > 0 &&
// 				    vision_sensor.get_by_sig(0, test_sig).x_middle_coord < 0) {
// 					turning = true;
// 					going = false;
// 				}
// 				rightMotors.moveVelocity(200);
// 				leftMotors.moveVelocity(200);
// 			} else {
// 				rightMotors.moveVelocity(0);
// 				leftMotors.moveVelocity(0);
// 				going = false;
// 				active = false;
// 			}
// 		}
// 		while (turning) {
// 			if (vision_sensor.get_by_sig(0, test_sig).x_middle_coord > 0) {
// 				arms::chassis::turn(1, 100);
// 			} else if (vision_sensor.get_by_sig(0, test_sig).x_middle_coord < 0) {
// 				arms::chassis::turn(-1, 100);
// 			} else if (vision_sensor.get_by_sig(0, test_sig).x_middle_coord == 0) {
// 				turning = false;
// 			}
// 		}
// 	}
// }

void align() {
	visiondetect::detected_object_s_t found;
	found = advanced_vision.detect_object(shirt);
	bool turning;
	bool going;

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
			while (found.apprx_distance >= 4) {
				arms::chassis::move(1, 100);
			}
			going = false;
		}
	}
}
// pros::lcd::set_text(1, "Area: " + std::to_string(found.area));
// pros::lcd::set_text(2, "Dist: " + std::to_string(found.apprx_distance));
// pros::lcd::set_text(3, "Valid: " + std::to_string(found.valid));
// //show x and y position
// pros::lcd::set_text(4, "X: " + std::to_string(found.x_px));
// pros::lcd::set_text(5, "Y: " + std::to_string(found.y_px));
} // namespace deFenestration::vision
