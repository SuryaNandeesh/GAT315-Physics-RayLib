#include "Fireworks.h"

Particle particles[MAX_PARTICLES];

void InitFireworks(Vector2 position) {
    // Initialization logic for fireworks
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].position = position;
        particles[i].velocity = (Vector2){ GetRandomValue(-5, 5), GetRandomValue(-20, -10) };
        particles[i].color = (Color){ GetRandomValue(50, 255), GetRandomValue(50, 255), GetRandomValue(50, 255), 255 };
        particles[i].radius = GetRandomValue(2, 4);
        particles[i].lifespan = GetRandomValue(30, 60);
    }
}

void LaunchFireworks(Vector2 position) {
    // Logic to launch fireworks at a specific position
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].position = position;
        particles[i].velocity = (Vector2){ GetRandomValue(-5, 5), GetRandomValue(-20, -10) };
        particles[i].color = (Color){ GetRandomValue(50, 255), GetRandomValue(50, 255), GetRandomValue(50, 255), 255 };
        particles[i].radius = GetRandomValue(2, 4);
        particles[i].lifespan = GetRandomValue(30, 60);
    }
}

void UpdateFireworks() {
    // Update logic for fireworks
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].position.x += particles[i].velocity.x;
        particles[i].position.y += particles[i].velocity.y;
        particles[i].velocity.y += 0.2f; // Apply gravity
        particles[i].lifespan--;

        if (particles[i].lifespan <= 0) {
            particles[i].position = (Vector2){ -100, -100 }; // Reset particle
        }
    }
}

void DrawFireworks() {
    // Drawing logic for fireworks
    for (int i = 0; i < MAX_PARTICLES; i++) {
        DrawCircleV(particles[i].position, particles[i].radius, particles[i].color);
    }
}
