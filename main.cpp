#include <iostream>
#include "Pendulum.h"
#include "raylib.h"

using namespace std;

int main()
{
	InitWindow(800, 600, "pendulum system");
	SetTargetFPS(60);
	Pendulum p(Arm(1.57, 0, 100, 10), Arm(1.57, 0, 100, 10), 400, 100);
	while (!WindowShouldClose())
	{
		double dt = GetFrameTime();
		p.update(dt, 9.81);
		BeginDrawing();
		ClearBackground(BLACK);
		p.draw();
		system("cls");
		EndDrawing();
	}
	CloseWindow();
	system("cls");
	return 0;
}
