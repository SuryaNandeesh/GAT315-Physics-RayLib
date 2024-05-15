#include "raylib.h"
#include "World.h"
#include <stdio.h>
int main(void)
{
	InitWindow(800, 450, "raylib [core] example - basic window");
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
		EndDrawing();
	}
	CloseWindow();

    // Create bodies
    Body* body1 = CreateBody();
    Body* body2 = CreateBody();
    Body* body3 = CreateBody();

    // Destroy a body
    DestroyBody(body2);

    // Update and draw bodies
    Body* body = bodies;
    while (body) {
        // Update body position
        // Draw body

        body = body->next;
    }
	return 0;
}