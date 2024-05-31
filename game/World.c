#include "world.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

ncBody* ncBodies = NULL;
int ncBodyCount = 0;
Vector2 ncGravity;

ncBody* CreateBody(Vector2 position, float mass, ncBodyType bodyType)
{
	ncBody* body = (ncBody*)malloc(sizeof(ncBody));
	assert(body);
	memset(body, 0, sizeof(ncBody));

	body->position = position;
	body->mass = mass;
	body->inverseMass = (bodyType == BT_DYNAMIC) ? 1 / mass : 0;
	body->type = bodyType;
	body->force = (Vector2){ 0, 0 };

	return body;
}

void AddBody(ncBody* body)
{
	assert(body);

	body->prev = (NULL);
	body->next = ncBodies;
	if (ncBodies) ncBodies->prev = body;
	ncBodies = body;
	ncBodyCount++;
}

void DestroyBody(ncBody* body)
{
	assert(body);
	if (body->prev) body->prev->next = body->next;
	if (body->next) body->next->prev = body->prev;
	if (body == ncBodies) ncBodies = body->next;
	ncBodyCount--;
	free(body);
}

void DestroyAllBodies()
{
	ncBody* body = ncBodies;
	while (body)
	{
		ncBody* temp = body->next;
		free(body);
		body = temp;
	}
	ncBodyCount = 0;
	ncBodies = NULL;
}
