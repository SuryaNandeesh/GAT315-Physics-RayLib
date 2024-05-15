#pragma once
#ifndef BODY_H
#define BODY_H

#include <main.c>
typedef struct Body
{
	// force -> acceleration -> velocity -> position
	Vector2 position;
	Vector2 velocity;
	Vector2 force;

	struct Body* next;
	struct Body* prev;
} Body;

#endif