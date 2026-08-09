#include "Pendulum.h"

Pendulum::Pendulum(Arm arm1, Arm arm2, double pivotX, double pivotY)
{
	this->arm1 = arm1;
	this->arm2 = arm2;
	this->pivotX = pivotX;
	this->pivotY = pivotY;
}

Pendulum::Pendulum()
{
	arm1.angle = 1.57;
	arm1.angularvelocity = 0;
	arm2.angle = 1.57;
	arm2.angularvelocity = 0;
	pivotX = 0;
	pivotY = 0;
}
Arm Pendulum::getArm2()
{
	return arm2;
}
Arm Pendulum::getArm1()
{
	return arm1;
}
double Pendulum::getPivotX()
{
	return pivotX;
}
double Pendulum::getPivotY()
{
	return pivotY;
}
void Pendulum::update()
{
}
void Pendulum::draw()
{
}
