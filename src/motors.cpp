#include "main.h"

// Driving Motors
pros::Motor left_mtr(9,MOTOR_GEARSET_18,false,MOTOR_ENCODER_ROTATIONS);
pros::Motor right_mtr(10,MOTOR_GEARSET_18,true,MOTOR_ENCODER_ROTATIONS);
pros::Motor r_left_mtr(19,MOTOR_GEARSET_18,false,MOTOR_ENCODER_ROTATIONS);
pros::Motor r_right_mtr(20,MOTOR_GEARSET_18,true,MOTOR_ENCODER_ROTATIONS);

// Arm & Claw Motors
pros::Motor claw_mtr(7,MOTOR_GEARSET_36,false,MOTOR_ENCODER_ROTATIONS);
pros::Motor arm_mtr(8,MOTOR_GEARSET_36,false,MOTOR_ENCODER_ROTATIONS);
