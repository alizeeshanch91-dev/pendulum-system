#include "Arm.h"
#include <cassert>

Arm::Arm(double angle, double angularVelocity, double lenght, double mass)
{
	assert(lenght > 0);
	assert(mass > 0);
	this->angle = angle;
	this->angularvelocity = angularVelocity;
}
Arm::Arm()
{
	angle = 0;
	angularvelocity = 0;
}
double Arm::getLength() const
{
	return length;
}
double Arm::getMass() const
{
	return mass;
}
