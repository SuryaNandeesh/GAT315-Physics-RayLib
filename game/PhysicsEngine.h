#pragma once
#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

typedef struct {
    float position[2];
    float velocity[2];
    float force[2];
} ncBody;

void SemiImplicitEuler(ncBody* body, float timestep);

#endif
