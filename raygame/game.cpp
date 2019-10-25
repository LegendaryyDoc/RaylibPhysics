#include "raylib/raylib.h"
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

	bool mb0 = IsMouseButtonPressed(0);
	bool mb1 = IsMouseButtonPressed(1);

	if (mb0 || mb1)
	{
		physObjects.emplace_back();
		std::cout << "Added a physics object!" << std::endl;

		auto& babyPhys = physObjects[physObjects.size() - 1];
		auto mousePos = GetMousePosition();
		babyPhys.pos = { mousePos.x, mousePos.y };
		babyPhys.addForce({ 0,1000 });

		if (mb0)
		{
			babyPhys.collider = circle{ 15.0f };
		}
		else
		{
			babyPhys.collider = aabb{ {15,15} };
		}
	}
}

void game::tickPhys()
{
	accumulatedFixedTime -= targetFixedStep;

	for (auto& i : physObjects)
	{
		i.tickPhys(targetFixedStep);
	}

	for (auto &i : physObjects)
	{
		for (auto &j : physObjects)
		{	
			//skip self
			if (&i == &j) { continue; }

			bool collision = false;

			i.collider.match([i, j, &collision](circle c) { if (checkCircleX(i.pos, c, j.pos, j.collider)) { collision = true; } },
				[i, j, &collision](aabb a) {if (checkAABBX(i.pos, a, j.pos, j.collider)) { collision = true; }});

			if (collision) { resolvePhysBodies(i, j); }
		}
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
