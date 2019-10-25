#include "physics.h"
#include "raylib/raylib.h"

physObject::physObject()
{
	pos = { 0,0 };
	vel = { 0,0 };
	forces = { 0,0 };

	mass = 1.0f;
	drag = 0.0f;
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

void physObject::addImpluse(glm::vec2 impulse)
{
	vel += impulse * (1.0f / mass);
}

void physObject::addAccel(glm::vec2 accel)
{
	// TODO: implement this
	assert(false);
}

void physObject::addVelcityChange(glm::vec2 delta)
{
	vel += delta;
}
