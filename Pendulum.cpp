#include "Pendulum.h"
#include "raylib.h"
#include <cmath>
#include <iostream>
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
void Pendulum::update(double dt,double gravity)
{
	double L1 = arm1.getLength();
	double m1 = arm1.getMass();
	double L2 = arm2.getLength();
	double m2 = arm2.getMass();
	double theta1 = arm1.angle;
	double theta2 = arm2.angle;
	double omega1 = arm1.angularvelocity;
	double omega2 = arm2.angularvelocity;
	double delta = theta1 - theta2;
	double M = 2*arm1.getMass() + arm2.getMass();
	double denom1 = L1 * (2 * m1 + m2 - m2 * cos(2 * delta));
	double denom2 = L2 * (2 * m1 + m2 - m2 * cos(2 * delta));
	// A: primary gravity torque
	double A = -gravity * M * sin(theta1);
	// B: second gravity effect
	double B = -m2 * gravity * sin(theta1 - 2 * theta2);
	// C: tug torque
	double C = -2 * sin(delta) * m2 * (omega2 * omega2 * L2 + omega1 * omega1 * L1 * cos(delta));
	// angular acceleration of the first arm
	double angular_acc_1 = (A + B + C) / denom1;

	// D: drive acceleration from arm 1
	double D = omega1 * omega1 * L1 * (m1 + m2);
	// E: base gravity transmition
	double E = gravity * (m1 + m2) * cos(theta1);
	// F: arm 2 speed feedback
	double F = omega2 * omega2 * L2 * m2 * cos(delta);
	// angular accerlation of the second arm
	double angular_acc_2 = (2 * sin(delta) * (D + E + F)) / (denom2);

	// semi-implicit Euler integration: velocity first, then angle
	arm1.angularvelocity += angular_acc_1 * dt;
	arm2.angularvelocity += angular_acc_2 * dt;
	arm1.angle += arm1.angularvelocity * dt;
	arm2.angle += arm2.angularvelocity * dt;
}
void Pendulum::draw()
{
	double L1 = arm1.getLength();
	double L2 = arm2.getLength();
	double theta1 = arm1.angle;
	double theta2 = arm2.angle;
	double bob1X = pivotX + L1 * sin(theta1);
	double bob1Y = pivotY + L1 * cos(theta1);
	double bob2X = bob1X + L2 * sin(theta2);
	double bob2Y = bob1Y + L2 * cos(theta2);
	DrawLine((int)pivotX, (int)pivotY, (int)bob1X, (int)bob1Y, WHITE);
	DrawLine((int)bob1X, (int)bob1Y, (int)bob2X, (int)bob2Y, WHITE);
	DrawCircle((int)bob1X, (int)bob1Y, 10, RED);
	DrawCircle((int)bob2X, (int)bob2Y, 10, BLUE);
}
