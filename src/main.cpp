/*
  Copyright (c) 2019-2023 7701F

  This software is provided 'as-is', without any express or implied warranty. In no event
  will the authors be held liable for any damages arising from the use of this software.
*/
#include "7701.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	/* ARMS & Sylib initialization */
	arms::init();
	sylib::initialize();

	/* Initialize Controler */
	master.print(0, 0, "");
	pros::delay(50);
	master.print(1, 0, "");
	pros::delay(50);
	master.print(2, 0, deFenestration::CODENAME.c_str());
	pros::delay(50);

	// set optical sensor LED to 100% brightness
	rollerSensor.set_led_pwm(100);

	/* Inititalize Flywheel */
	pros::Task fwTask(deFenestration::Flywheel::FwControlTask);

	/* Controller Status Display */
	pros::Task controllerTask{[=] {
		/*
		 * Only print every 50ms, the controller text update rate is slow.
		 * Any input faster than this will be dropped.
		 */
		int count;
		std::string autonName;
		while (true) {
			if (count == 10) {
				std::stringstream line1;
				line1 << "Brake: " << (pbrake ? "ON" : "OFF") << " FW:" << (fwON ? "Y" : "N") << "\r";
				master.print(0, 0, line1.str().c_str());
			} else if (count == 5) {
				std::stringstream autonstr;
				int selAuton = abs(arms::selector::auton);
				if (selAuton != 0) {
					autonName = arms::autons[selAuton - 1];
				} else {
					autonName = "SKLS";
				}

				if (arms::selector::auton > 0) {
					autonstr << "Auton: R " << autonName << "\r";
				} else if (arms::selector::auton < 0) {
					autonstr << "Auton: B " << autonName << "\r";
				} else if (arms::selector::auton == 0) {
					autonstr << "Auton: SKLS"
					         << "\r";
				}

				master.print(1, 0, autonstr.str().c_str());
			}

			count++;
			count %= 15;

			// indexLights.set_all(0xE62169);
			pros::delay(10);
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
		printf("Disabled loop");

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
