#include "globals.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::MotorGroup DriveL({1, 2, 3});
pros::MotorGroup DriveR({-4, -5, -6});
pros::Motor Cata({-8});
pros::Motor Intake({-9});
pros::ADIDigitalOut PneuHoriz('C', false);
pros::ADIDigitalOut PneuVert('B', false);
pros::ADIDigitalOut PnueHang('D', true );