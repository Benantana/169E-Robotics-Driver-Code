#include "globals.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::MotorGroup DriveL({-20, -19, -18});
pros::MotorGroup DriveR({15, 14, 13});
pros::Motor Intake({10});
pros::Motor Chain({-7});
pros::adi::DigitalOut MogoPneu('A', false);
// pros::ADIDigitalOut PneuVert('B', false);
// pros::ADIDigitalOut PnueHang('D', true );