#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <Body.h>
extern Body* bodies;
extern int bodyCount;

Body* CreateBody();
void DestroyBody(Body* body);

#endif
