#include "physics.h"
#include "raylib.h"

physObject::physObject()
{
	pos = { 0,0 };
	vel = { 0,0 };
	forces = { 0,0 };

	mass = 1.0f;
	drag = 1.0f;
}

void physObject::tickPhys(float delta)
{
	// integrating forces into velocity
	vel += forces * delta;
	forces = { 0,0 };

	// integrate linear drag
	vel *= 1.0f - delta * drag;

	// integrating velocity into position
	pos += vel * delta;

}

void physObject::draw() const
{
	DrawCircleLines(pos.x, pos.y, 15.0f, PINK);
}

void physObject::addForce(glm::vec2 force)
{
	forces += force * (1.0f / mass);
}
