#pragma once
#ifndef FIREWORKS_H
#define FIREWORKS_H

#include "raylib.h"

#define MAX_PARTICLES 100

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Color color;
    float radius;
    int lifespan;
} Particle;

void InitFireworks(Vector2 position);
void LaunchFireworks(Vector2 position);
void UpdateFireworks();
void DrawFireworks();

#endif
