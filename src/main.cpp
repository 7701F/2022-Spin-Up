#include "main.h"

int arm_speed = 60;
int claw_speed = 30;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
// void on_center_button() {
// 	static bool pressed = false;
// 	pressed = !pressed;
// 	if (pressed) {
// 		pros::lcd::set_text(2, "I was pressed!");
// 	} else {
// 		pros::lcd::clear_line(2);
// 	}
// }

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	
	pros::lcd::print(0, "       .---.");
	pros::lcd::print(1, "      /     \\");
	pros::lcd::print(2, "      \\.@-@./");
	pros::lcd::print(3, "      /`\\_/`\\");
	pros::lcd::print(4, "     //  _  \\");
	pros::lcd::print(5, "    | \\     )|_");
	pros::lcd::print(6, "   /`\\_`>  <_/ \\");
	pros::lcd::print(7, "   \\__/'---'\\__/");

	// pros::lcd::register_btn1_cb();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	pros::lcd::clear();
	pros::lcd::print(0, "Disabled by FMS/Competition Switch");
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
void competition_initialize() {}


// Distance in inches, Speed in rpms, Wait in milliseconds
void drive(double distance, int speed, int wait) {

    double wheel_radius = 2.065; //inches
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
void turn(double degrees, int speed, int wait) {

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

void grab(double degrees, int speed, int wait) {

    double one_rotation_turn_degrees = 115; //customize to your robot
    double rotations = degrees/one_rotation_turn_degrees;
    claw_mtr.move_relative(rotations, speed);

    rotations += claw_mtr.get_position();

    while (!((claw_mtr.get_position() < rotations + 0.5) && (claw_mtr.get_position() > rotations -0.5 ))) {
        pros::delay(20);
    }
    
    pros::delay(wait);

}

void lift(double degrees, int speed, int wait) {

    double one_rotation_turn_degrees = 115; //customize to your robot
    double rotations = degrees/one_rotation_turn_degrees;
    arm_mtr.move_relative(rotations, speed);

    rotations += arm_mtr.get_position();

    while (!((arm_mtr.get_position() < rotations + 0.5) && (arm_mtr.get_position() > rotations -0.5 ))) {
        pros::delay(20);
    }
    
    pros::delay(wait);

}

void autonomous() {

//   drive(60,100,1000);
//   turn(-360,100,1000);
//   lift(-180,100,1000);
//   grab(-60,100,1000);
	// turn(-90, 100, 1000);`	z
	drive(34, 100, 1000);
	drive(34,-100, 1000);
	// grab(-35, 100, 1000);
	// turn(180, 100, 1000);
	// drive(34, 100, 1000);
	// turn(-90, 100, 1000);
	// drive(20, 100, 1000);
	// lift(500, 100 ,1000);

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
	
	// Run Loop
	while (true) {
		// %d %d %d
		pros::lcd::print(0, "%d %d    .---.", (master.get_analog(ANALOG_LEFT_X)) >> 1,
		                 (master.get_analog(ANALOG_LEFT_Y)) >> 0);

		// Arcade Steering
		int forward_backward = master.get_analog(ANALOG_LEFT_Y);
		int left_right = master.get_analog(ANALOG_LEFT_X);
		left_mtr.move(forward_backward + left_right);
		right_mtr.move(forward_backward - left_right);

		// Arm Control
		if(master.get_digital(DIGITAL_L2)) {
			arm_mtr.move_velocity(arm_speed);
			arm1_mtr.move_velocity(-arm_speed);
		}
		else if (master.get_digital(DIGITAL_L1)) {
			arm_mtr.move_velocity(-arm_speed);
			arm1_mtr.move_velocity(arm_speed);
		}
		else {
			arm_mtr.move_velocity(0);
			arm1_mtr.move_velocity(0);
		}

		// Grab Control
		if(master.get_digital(DIGITAL_R1)) {
			claw_mtr.move_velocity(-claw_speed);
		}
		else if (master.get_digital(DIGITAL_R2)) {
			claw_mtr.move_velocity(claw_speed);
		}
		else {
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
