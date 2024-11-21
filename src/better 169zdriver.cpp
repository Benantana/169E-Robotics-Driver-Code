#include "main.h"
#include "../include/pros/misc.h"
#include "globals.h"
#include <chrono>
#include <thread>
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button()
{
	static bool pressed = false;
	pressed = !pressed;
	if (pressed)
	{
		pros::lcd::set_text(2, "I was pressed!");
	}
	else
	{
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);

	Cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
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
void moveBot(int Units)
{
	DriveL.move_relative(Units, 60);
	DriveR.move_relative(Units, 60);
}
void spinBot(int Turnits)
{
	DriveL.move_relative(Turnits, 60);
	DriveR.move_relative(-Turnits, 60);
}
void autonomous()
{
	PneuVert.set_value(true); //start back of bar, horz wings outs
	pros::delay(500);
	moveBot(100); // move forward enough so that you can push triball out of alley (wings agianst it)
	pros::delay(1000);
	spinBot(45); // turn 45 degrees here, where triball is "hit" out
	PneuVert.set_value(false); //wings back in
	pros::delay(100); 
	spinbot(200); // gets the bot alligned with middle bar
	pros::delay(1000); 
	moveBot(5000); //drives up under the bar and touches with zips
	
	
}
void prog()
{
	moveBot(-1150); //ram the two triballs (red) into goal and score
	pros::delay(1500);
	spinBot(-550); 	// turn towards "infront of" matchload bar
	pros::delay(1500);
	moveBot(850); 	// move diagonally infront of where matchload bar would be
	pros::delay(1500);
	spinBot(250); 	// turn so you'll ram right up against the matchload bar with the back
	pros::delay(550) 
	moveBot(-900); 	// ram right against the matchload bar, perpendicular to the horizontal mid bar (so if you go forward from there, you'll hit the big bar)
	PneuVert.set_value(true); // wing out, touch matchload bar
	pros::delay(550);
	Cata.move(80); 	//however many rotations it takes to shoot the catapult 44 times
	pros::delay(200);
    PneuVert.set_value(false);
	movebot(1000); //run into the mid bar corner
    pros::delay(200);
    spinBot(500); //turn to the right
    pros::delay(300);
    movebot(2000); //straight into the opposite end of the bar
    pros::delay(200);
    movebot(-400); //move back away from the bar, 
    pros::delay(200);
    movebot(400); //ram back into bar
    pros::delay(200);
    spinbot::(400); // turn to be perpendicular with bar again, but now facing away 
    movebot(300); //move it away from bar, so you can turn
    pros::delay(200);
    spinbot::(800); // turn 90 degrees, facing straight into the wall
    pros::delay(500);
    spinbot::(800); // turn 90 degrees again, parrallel to the short bars 
    pros::delay(500); 
    movebot(1000); // go forward up to blue defensive side matchload bar, keep going into goal
    pros:delay(50); 
    movebot(-100) // go back a bit to be able to turn (https://www.youtube.com/watch?v=b8F_Gk15MQk used for inspiration)
    pros:delay(50);
    spinbot(35); //spin a bit ~35 degrees


	DriveL.move_relative(-10000, 2);
	DriveR.move_relative(-10000, 2);
	pros::delay(1000);
	Cata.move(80);
	pros::delay(1000000000);
}
/**
 * moveBot(-1000)
 * moveBot(1000)
 *
 *
 *
 * moveBot(450)
 *
 *
 */
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
void opcontrol()
{
	bool Horiz = false;
	bool Vert = false;
	bool Hang = true 

	// Driving
	while (true)
	{

		// Arcade control scheme
		int dir = master.get_analog(ANALOG_LEFT_Y);	  // Gets amount forward/backward from left joystick
		int turn = master.get_analog(ANALOG_RIGHT_X); // Gets the turn left/right from right joystick
		DriveL = -(dir + turn);						  // Sets left motor voltage
		DriveR = -(dir - turn);						  // Sets right motor voltage

		if (master.get_digital(DIGITAL_B))
		{
			Cata.move(127);
		}
		else
		{
			Cata.brake();
		}
		while (master.get_digital(DIGITAL_R2))
		{
			Intake.move(127);
		}
		while (master.get_digital(DIGITAL_R1))
		{
			Intake.move(-127);
		}
		while (master.get_digital(DIGITAL_L1))
		{
			Intake.brake();
		}
		if (master.get_digital_new_press(DIGITAL_UP))
		{
			Horiz = (!Horiz);
			PneuHoriz.set_value(Horiz);
		}
		if (master.get_digital_new_press(DIGITAL_DOWN))
		{
			Vert = (!Vert);
			PneuVert.set_value(Vert);
		}
		if (master.get_digital_new_press(DIGITAL_Y))
		{
			Hang = (!Hang);
			PneuHang.set_value(Hang);
		}
	}
}