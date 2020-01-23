#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}


// Distance in inches, Speed in rpms, Wait in milliseconds
void drive(double distance, int speed, int wait){

    double wheel_radius = 2; //inches
    double const pi = 3.14159265;
    //1 rotation will move the robot 2*pi*wheel_radius inches
    double rotations = distance/(pi*2*wheel_radius);
    left_mtr.move_relative(rotations, speed);
    right_mtr.move_relative(rotations, speed);

    rotations += left_mtr.get_position();

    while (!((left_mtr.get_position() < rotations + 0.5) && (left_mtr.get_position() > rotations - 0.5 ))) {
        pros::delay(5);
	}

    pros::delay(wait);

}

// Degrees of turn.  Speed is RPM, Wait is milliseconds
void turn(double degrees, int speed, int wait){

    double one_rotation_turn_degrees = 115; //customize to your robot
    double rotations = degrees/one_rotation_turn_degrees;
    left_mtr.move_relative(rotations, speed);
    right_mtr.move_relative(-rotations, speed);

    rotations += left_mtr.get_position();

    while (!((left_mtr.get_position() < rotations + 0.5) && (left_mtr.get_position() > rotations -0.5 ))) {
        pros::delay(20);
    }
    
    pros::delay(wait);

}



void autonomous() {

  //front_left_mtr.move_relative(10, 100);
  drive(60,100,1000);
  drive(-24,100,1000);
  drive(24,100,1000);
  drive(-60,100,1000);
  turn(360,100,1000);
  turn(-180,100,1000);
  turn(100,100,1000);
  turn(-360,100,1000);
  turn(360, 100, 1000);

}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	
	// Controller
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	// Variables
	int arm_speed = 45;
	int claw_speed = 45;
	
	// Run Loop
	while (true) {
		// %d %d %d
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

		// Arcade Steering
		int forward_backward = master.get_analog(ANALOG_LEFT_Y);
		int left_right = master.get_analog(ANALOG_LEFT_X);
		left_mtr.move(forward_backward + left_right);
		right_mtr.move(forward_backward - left_right);

		// Arm Control
		if(master.get_digital(DIGITAL_L2)){
			arm_mtr.move_velocity(arm_speed);
		}
		else if (master.get_digital(DIGITAL_L1)){
			arm_mtr.move_velocity(-arm_speed);
		}
		else{
			arm_mtr.move_velocity(0);
		}

		// Grab Control
		if(master.get_digital(DIGITAL_R1)){
			claw_mtr.move_velocity(-claw_speed);
		}
		else if (master.get_digital(DIGITAL_R2)){
			claw_mtr.move_velocity(claw_speed);
		}
		else{
			claw_mtr.move_velocity(0);
		}

		// Strafe
		// if(master.get_digital(DIGITAL_A)){
		// 	right_mtr.move_velocity(-127);
		// 	left_mtr.move_velocity(127);
		// 	r_right_mtr.move_velocity(127);
		// 	r_left_mtr.move_velocity(-127);
		// }
		// else if (master.get_digital(DIGITAL_Y)){
		// 	right_mtr.move_velocity(127);
		// 	left_mtr.move_velocity(-127);
		// 	r_right_mtr.move_velocity(-127);
		// 	r_left_mtr.move_velocity(127);
		// }
		// else{
		// 	// right_mtr.move_velocity(0);
		// 	// left_mtr.move_velocity(0);
		// 	// r_right_mtr.move_velocity(0);
		// 	// r_left_mtr.move_velocity(0);
		// }

		pros::delay(20);

	}
}
