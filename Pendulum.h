#pragma once
#include "Arm.h"

class Pendulum
{
private:
	Arm arm1;
	Arm arm2;
	double pivotX;
	double pivotY;
public:
	Pendulum(Arm arm1, Arm arm2, double pivotX, double pivotY);
	Pendulum();
	Arm getArm2();
	Arm getArm1();
	double getPivotX();
	double getPivotY();
	void update();
	void draw();
};
