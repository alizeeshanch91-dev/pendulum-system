#pragma once
struct Arm
{
	double angle;
	double angularvelocity;

	Arm(double angle, double angularVelocity, double lenght, double mass);
	Arm();
	double getLength() const;
	double getMass() const;

private:
	double length;
	double mass;
};
