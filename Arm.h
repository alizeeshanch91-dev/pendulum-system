#pragma once
struct Arm
{
	double angle;
	double angularvelocity;

	Arm(double angle, double angularVelocity, double length, double mass);
	Arm();
	double getLength() const;
	double getMass() const;

private:
	double length;
	double mass;
};
