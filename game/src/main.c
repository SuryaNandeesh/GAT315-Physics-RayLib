#include "body.h"
#include "world.h"
#include "mathf.h"
#include "force.h"
#include "integrator.h"
#include "render.h"
#include "editor.h"
#include "spring.h"
#include "collision.h"
#include "contact.h"

#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 100
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main(void)
{
	ncBody* selectedBody = NULL;
	ncBody* connectBody = NULL;
	ncContact_t* contacts = NULL;

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physics Engine");
	InitEditor();
	SetTargetFPS(60);

	float timeAccumulator = 0;

	// initialize world


	while (!WindowShouldClose())
	{
		// update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();
		float fixedTimestep = 1.0 / ncEditorData.timestepValue;
		ncGravity = (Vector2){ 0, -ncEditorData.gravityValue };


		Vector2 mousePosition = GetMousePosition();
		//ncScreenZoom += GetMouseWheelMove() * 0.2f;
		//ncScreenZoom += Clamp(ncScreenZoom, 0.1f, 10);

		UpdateEditor(mousePosition);

		selectedBody = GetBodyIntersect(ncBodies, mousePosition);
		if (selectedBody)
		{
			Vector2 screen = ConvertWorldToScreen(selectedBody->position);
			DrawCircleLines((int)screen.x, (int)screen.y, ConvertWorldToPixel(selectedBody->mass) + 5, YELLOW);
		}

		if (!ncEditorIntersect && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_ALT)))
		{
			ncBody* body = CreateBody(ConvertScreenToWorld(mousePosition), ncEditorData.massValue, ncEditorData.bodyTypeActive);
			body->color = (Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
			body->damping = ncEditorData.dampingValue;
			body->gravityScale = ncEditorData.gravityScaleValue;
			body->restitution = 0.82f;
			AddBody(body);
		}

		// connect spring
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && selectedBody) connectBody = selectedBody;
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && connectBody) DrawLineBodyToPosition(connectBody, mousePosition);
		if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && connectBody)
		{
			if (selectedBody && selectedBody != connectBody)
			{
				ncSpring_t* spring = CreateSpring(connectBody, selectedBody, Vector2Distance(connectBody->position, selectedBody->position), 20);
				AddSpring(spring);
			}
		}

		if (ncEditorData.reset)
		{
			DestroyAllSprings();
			DestroyAllBodies();
		}

		// apply force
		timeAccumulator += dt;
		while (timeAccumulator >= fixedTimestep)
		{
			timeAccumulator -= fixedTimestep;
			if (ncEditorData.simulate) continue;

			ApplyGravitation(ncBodies, ncEditorData.gravitationValue);
			ApplySpringForce(ncSprings);

			for (ncBody* body = ncBodies; body; body = body->next)
			{
				Step(body, dt);
			}
			DestroyAllContacts(&contacts);
			CreateContacts(ncBodies, &contacts);
			SeparateContacts(contacts);
			ResolveContacts(contacts);
		}


		// render
		BeginDrawing();
		ClearBackground(BLACK);

		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000 / fps), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAME: %.4f", dt), 10, 30, 20, LIME);
		DrawText(TextFormat("BODIES: %i", ncBodyCount), 10, 50, 20, LIME);


		// draw bodies
		for (ncBody* body = ncBodies; body; body = body->next)
		{
			Vector2 screen = ConvertWorldToScreen(body->position);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(body->mass * 0.5), body->color);
		}

		// draw contacts
		for (ncContact_t* contact = contacts; contact; contact = contact->next)
		{
			Vector2 screen1 = ConvertWorldToScreen(contact->body1->position);
			Vector2 screen2 = ConvertWorldToScreen(contact->body2->position);
			DrawCircle((int)screen1.x, (int)screen1.y, ConvertWorldToPixel(contact->body1->mass * 0.5), RED);
			DrawCircle((int)screen2.x, (int)screen2.y, ConvertWorldToPixel(contact->body2->mass * 0.5), RED);
		}

		// draw springs
		for (ncSpring_t* spring = ncSprings; spring; spring = spring->next)
		{
			Vector2 screen1 = ConvertWorldToScreen(spring->body1->position);
			Vector2 screen2 = ConvertWorldToScreen(spring->body2->position);
			DrawLine(screen1.x, screen1.y, screen2.x, screen2.y, YELLOW);
		}
		DrawEditor(mousePosition);

		EndDrawing();
	}
	CloseWindow();

	DestroyAllBodies();
	DestroyAllSprings();
	DestroyAllContacts(&contacts);

	_CrtDumpMemoryLeaks();

	return 0;
}