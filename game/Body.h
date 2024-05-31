#pragma once
#include <raylib.h>
#include <raymath.h>

typedef enum ncBodyType
{
	BT_STATIC,
	BT_KINEMATIC,
	BT_DYNAMIC
} ncBodyType;

typedef enum
{
	FM_FORCE,
	FM_IMPULSE,
	FM_VELOCITY
} ncForceMode;

typedef struct ncBody
{
	ncBodyType type;

	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 force;

	float mass;
	float inverseMass; // 1 / mass (static = 0)
	float gravityScale;
	float damping;
	float restitution;
	Color color;

	struct ncBody* prev;
	struct ncBody* next;

} ncBody;

inline void ApplyForce(ncBody* body, Vector2 force, ncForceMode forceMode)
{
	if (body->type != BT_DYNAMIC) return;

	switch (forceMode)
	{
	case FM_FORCE:
		body->force = Vector2Add(body->force, force);
		break;
	case FM_IMPULSE:
		// applies a sudden change in momentum
		body->velocity = Vector2Add(body->velocity, Vector2Scale(force, body->inverseMass));
		break;
	case FM_VELOCITY:
		body->velocity = force;
		break;
	}
}

inline void ClearForce(ncBody* body)
{
	body->force = Vector2Zero();
}

void Step(ncBody* body, float timestep);