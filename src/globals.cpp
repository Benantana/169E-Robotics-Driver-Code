#include "globals.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::MotorGroup DriveL({1, 2, 3});
pros::MotorGroup DriveR({-4, -5, -6});
pros::Motor Intake({-7});
pros::adi::DigitalOut MogoPneu('A', false);
// pros::ADIDigitalOut PneuVert('B', false);
// pros::ADIDigitalOut PnueHang('D', true );