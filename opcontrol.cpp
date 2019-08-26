#include "main.h"

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
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Controller secondary(pros::E_CONTROLLER_PARTNER);
	pros::Motor front_dtright(1);
	pros::Motor front_dtleft(10);
	pros::Motor back_dtright(2);
	pros::Motor back_dtleft(9);
	pros::Motor intake_v(14);
	pros::Motor intake_h(15);
	pros::Motor lift_left(16, true);
	pros::Motor lift_right(17);

	while (true) {
	front_dtleft.move(master.get_analog(ANALOG_LEFT_Y));
	back_dtleft.move(master.get_analog(ANALOG_LEFT_Y));
	front_dtright.move(master.get_analog(ANALOG_RIGHT_Y));
	back_dtright.move(master.get_analog(ANALOG_RIGHT_Y)); // tank drive

	//	int power	= master.get_analog(ANALOG_LEFT_Y);
	//	int turn = master.get_analog(ANALOG_RIGHT_X);
	//	int left = power + turn;
	//	int right = power - turn; // arcade control

	if (secondary.get_digital(DIGITAL_R1))	{
		intake_v.move_velocity(200);
	}
	else if (secondary.get_digital(DIGITAL_R2)){
		intake_v.move_velocity(-200);
	}
	else{
		intake_v.move_velocity(0);
	}
//angle adjustor controls :)

	if (secondary.get_digital(DIGITAL_L1)){
		intake_h.move_velocity(50);
	}
	else if (secondary.get_digital(DIGITAL_L2)){
		intake_h.move_velocity(-50);
	}
	else{
		intake_h.move_velocity(0);
	}
// conveyor controls	:)

if (master.get_digital(DIGITAL_R1)){
	lift_left.move_velocity(200);
	lift_right.move_velocity(200);
}
else if (master.get_digital(DIGITAL_R2)){
	lift_left.move_velocity(-200);
	lift_right.move_velocity(-200);
}
else {
	lift_left.move_velocity(0);
	lift_right.move_velocity(0);
}
// lift movement controls :)
	}
}
