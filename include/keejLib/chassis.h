#pragma once
#include "util.h"

namespace lib
{
    class chassis
    {
        private:
            lib::diffy* chass;
            pros::Imu* imu;
            pros::ADIEncoder* horizTracker = nullptr;
            pros::ADIEncoder* vertTracker = nullptr;
            point pos = {0,0};
            lib::robotConstants constants;
            pros::Task* odomTask = nullptr;
            double prevRotation = 0;

        public:
            chassis(lib::diffy& mtrs, pros::Imu& imu) : chass(&mtrs), imu(&imu){}
            chassis(lib::diffy& mtrs, pros::Imu& imu, lib::robotConstants constants) : chass(&mtrs), imu(&imu), constants(constants) {}
            chassis(lib::diffy& mtrs, pros::Imu& imu, std::vector<int> encoderPorts, lib::robotConstants constants);
            
            void updatePos();
            void initTracking();

            //1dpid
            void pidDrive(double target, double timeout, lib::pidConstants constants);
            void pidTurn(double target, double timeout, lib::pidConstants constants);
            void arcTurn(double target, double radius, double timeout, int dir, lib::pidConstants constants); 

            //1dmp
            std::vector<double> asymTrapezoidalProfile(double dist, double maxSpeed, double accel, double decel);
            void profiledDrive(double target, int endDelay);

            //2dpid
            void driveAngle(double target, double heading, double timeout, lib::pidConstants lCons, lib::pidConstants acons);
            std::vector<double> pidMTPVel(const point& target, double rotationBias, lib::pid* lCont, lib::pid* rCont);
            void pidMoveTo(const point& target, double timeout, lib::pidConstants lConstants, lib::pidConstants 
            rConstants, double rotationBias);
            void boomerang(const point& target, double timeout, double dLead, double thetaEnd, double rotationBias, lib::pidConstants lConstants, lib::pidConstants rConstants);
    };
}