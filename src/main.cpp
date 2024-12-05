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

void moveBot(double Inches)
{
	// (convert to degrees (take 36-48 gear ratio into account)/360)* arc formula (3.14*diameter)   This is to make it inches moving forward not random units
	DriveL.move_relative(((1.2 * Inches) / 360) * 3.14159 * 2.75, 60);
	DriveR.move_relative(((1.2 * Inches) / 360) * 3.14159 * 2.75, 60);
}
// This may been to be figured out, I have no clue how much I need to turn. Good luck!
void spinBot(double Turnits)
{
	DriveL.move_relative(Turnits, 60);
	DriveR.move_relative(-Turnits, 60);
}
void turnOnIntake()
{
	Intake.move(100);
}
void turnOffIntake()
{
	Intake.brake();
}
void turnOnChain()
{
	Chain.move(100);
}
void turnOffChain()
{
	Chain.brake();
}
void turnOnClamp()
{
	MogoPneu.set_value(true);
}
void turnOffClamp()
{
	MogoPneu.set_value(false);
}

void FlapJack()
{
	Chain.move_relative(-50, 100);
}
void autonomous()
{
	// PUT AUTON HERE FOR EACH CODE AND THEN GO TO PROJECT.PROS TO CHANGE THE PORT FOR EACH AUTON AND NAME. MAKE SURE YOU SAVE AFTER EACH CHANGE AND SAVE A FILE
}
void prog()
{
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
	bool Mogo = false;
	bool INtake = false;
	bool OUTtake = false;
	bool ChainOn = false;

	// Driving
	while (true)
	{

		// Tank control scheme
		int RightVol = master.get_analog(ANALOG_RIGHT_Y); // Gets amount forward/backward from left joystick
		int LeftVol = master.get_analog(ANALOG_LEFT_Y);	  // Gets the turn left/right from right joystick
		DriveL = LeftVol;								  // Sets left motor voltage
		DriveR = RightVol;								  // Sets right motor voltage

		if (master.get_digital_new_press(DIGITAL_R2))
		{
			if (INtake == false)
			{
				Intake.move(100);
				OUTtake = false;
				INtake = true;
			}
			else
			{
				Intake.brake();
				INtake = false;
			}
		}
		if (master.get_digital_new_press(DIGITAL_R1))
		{
			if (OUTtake == false)
			{
				Intake.move(-100);
				INtake = false;
				OUTtake = true;
			}
			else
			{
				Intake.brake();
				OUTtake = false;
			}
		}
		if (master.get_digital_new_press(DIGITAL_L1))
		{
			if (ChainOn == false)
			{
				Chain.move(100);
				ChainOn = true;
			}
			else
			{
				Chain.brake();
				ChainOn = false;
			}
		}
		// Flapjack Button
		if (master.get_digital_new_press(DIGITAL_B))
		{
			FlapJack();
		}

		if (master.get_digital_new_press(DIGITAL_L2))
		{
			Mogo = (!Mogo);
			MogoPneu.set_value(Mogo);
		}
	}
}