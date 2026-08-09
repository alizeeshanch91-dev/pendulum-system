#include <iostream>
#include "Pendulum.h"
#include "raylib.h"
using namespace std;

int main()
{
    double angularVelocityInput;
    bool validInput;

    cout << "Enter starting angular velocity for arm 1 (-10 to 10, recommended: 0): ";

    do
    {
        cin >> angularVelocityInput;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "That's not a number. Try again: ";
            validInput = false;
        }
        else if (angularVelocityInput < -10 || angularVelocityInput > 10)
        {
            cout << "Out of range. Enter a value between -10 and 10: ";
            validInput = false;
        }
        else
        {
            validInput = true;
        }

    } while (!validInput);
    InitWindow(800, 600, "pendulum system");
    SetTargetFPS(60);
    Pendulum p(Arm(1.57, angularVelocityInput, 100, 10), Arm(1.57, 0, 100, 10), 400, 100,GRAY);

    Pendulum twin(Arm(1.5701, 0, 100, 10), Arm(1.5701, 0, 100, 10), 400, 100,WHITE);
    bool twinSpawned = false;

    while (!WindowShouldClose())
    {
        double dt = GetFrameTime();

        if (IsKeyPressed(KEY_SPACE) && !twinSpawned)
        {
            twinSpawned = true;
        }

        p.update(dt, 9.81);
        if (twinSpawned)
        {
            twin.update(dt, 9.81);
        }

        BeginDrawing();
        ClearBackground(BLACK);
        p.draw(300);
        if (twinSpawned)
        {
            twin.draw(550);
        }
        DrawText(TextFormat("Gravity: %.2f", 9.81), 10, 500, 20, GREEN);
        DrawText(TextFormat("Initial angular velocity: %.2f", angularVelocityInput), 10, 535, 20, GREEN);
        DrawText("NOTE: Press space to summon second pendulum with default angular velocity(0). Only Grey pendulum moves with custom velocity", 10, 575,10, GRAY);
        EndDrawing();
    }
    CloseWindow();
    system("cls");
    return 0;
}
