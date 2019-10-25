#include "raylib.h"
#include "game.h"
#include <iostream>

game::game()
{
	targetFixedStep = 1.0f / 30.0f;
	accumulatedFixedTime = 0.0f;
}

void game::init()
{
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);
}

void game::tick()
{
	accumulatedFixedTime += GetFrameTime();

	if (IsMouseButtonPressed(0))
	{
		physObjects.emplace_back();
		std::cout << "Added a physics object!" << std::endl;

		auto& babyPhys = physObjects[physObjects.size() - 1];
		auto mousePos = GetMousePosition();
		babyPhys.pos = { mousePos.x, mousePos.y };
		babyPhys.addForce({0,1000});
	}
}

void game::tickPhys()
{
	accumulatedFixedTime -= targetFixedStep;

	for (auto& i : physObjects)
	{
		i.tickPhys(targetFixedStep);
	}
}

void game::draw() const
{
	BeginDrawing();

	ClearBackground(RED);
	
	for (const auto& i : physObjects)
	{
		i.draw();
	}

	EndDrawing();
}

void game::exit()
{
	CloseWindow();
}

bool game::shouldClose() const
{
	return WindowShouldClose();
}

bool game::shouldPhysics() const
{
	return accumulatedFixedTime >= targetFixedStep;
}
