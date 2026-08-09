#pragma once
#include "Arm.h"
#include "raylib.h"
class Pendulum
{
private:
	Arm arm1;
	Arm arm2;
	double pivotX;
	double pivotY;
	Color armColor;
public:
	Pendulum(Arm arm1, Arm arm2, double pivotX, double pivotY,Color armColor);
	Pendulum();
	Arm getArm2();
	Arm getArm1();
	double getPivotX();
	double getPivotY();
	void update(double dt, double gravity);
	void draw(int textX);
};
