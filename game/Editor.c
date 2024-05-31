#include "editor.h"
#include "body.h"
#include "render.h"
#define RAYGUI_IMPLEMENTATION
#include "../raygui-master/src/raygui.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;
ncEditorData_t ncEditorData;

Rectangle editorRect;

Texture2D cursorTexture;

void InitEditor()
{
    GuiLoadStyle("raygui/styles/cyber/style_cyber.rgs");

    Image image = LoadImage("resources/reticle.png");
    cursorTexture = LoadTextureFromImage(image);
    UnloadImage(image);
    HideCursor();

    ncEditorData.anchor01 = (Vector2){ 840, 24 };
    ncEditorData.editorBoxActive = true;


    // body
    ncEditorData.bodyTypeEditMode = false;
    ncEditorData.bodyTypeActive = 0;
    ncEditorData.massValue = 1;
    ncEditorData.dampingValue = 0;
    ncEditorData.gravityScaleValue = 0;
    ncEditorData.stiffnessValue = 10;

    // world
    ncEditorData.gravityValue = 0;
    ncEditorData.gravitationValue = 0;
    ncEditorData.timestepValue = 50;

    editorRect = (Rectangle){ ncEditorData.anchor01.x + 0, ncEditorData.anchor01.y + 0, 240, 576 };
}

void UpdateEditor(Vector2 position)
{
    if (IsKeyPressed(KEY_TAB)) ncEditorData.editorBoxActive = !ncEditorData.editorBoxActive;

    ncEditorIntersect = (ncEditorData.editorBoxActive && CheckCollisionPointRec(position, editorRect));
}

void DrawEditor(Vector2 position)
{
    if (ncEditorData.bodyTypeEditMode) GuiLock();

    if (ncEditorData.editorBoxActive)
    {
        ncEditorData.editorBoxActive = !GuiWindowBox((Rectangle) { ncEditorData.anchor01.x + 0, ncEditorData.anchor01.y + 0, 300, 576 }, "Editor");
        GuiGroupBox((Rectangle) { ncEditorData.anchor01.x + 16, ncEditorData.anchor01.y + 40, 268, 192 }, "Body");
        GuiGroupBox((Rectangle) { ncEditorData.anchor01.x + 16, ncEditorData.anchor01.y + 240, 268, 144 }, "World");
        GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 116, ncEditorData.anchor01.y + 80, 120, 16 }, "Mass", TextFormat("%0.2f", ncEditorData.massValue), & ncEditorData.massValue, 0.1f, 10);
        GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 116, ncEditorData.anchor01.y + 104, 120, 16 }, "Damping", TextFormat("%0.2f", ncEditorData.dampingValue), & ncEditorData.dampingValue, 0, 1);
        GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 116, ncEditorData.anchor01.y + 128, 120, 16 }, "Gravity Scale", TextFormat("%0.2f", ncEditorData.gravityScaleValue), & ncEditorData.gravityScaleValue, 0, 1);
        GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 116, ncEditorData.anchor01.y + 152, 120, 16 }, "Stiffness", TextFormat("%0.2f", ncEditorData.stiffnessValue), & ncEditorData.stiffnessValue, 0, 1);
        GuiSlider((Rectangle) { ncEditorData.anchor01.x + 116, ncEditorData.anchor01.y + 248, 120, 16 }, "Gravity", TextFormat("%0.2f", ncEditorData.gravityValue), & ncEditorData.gravityValue, -100, 100);
        GuiSlider((Rectangle) { ncEditorData.anchor01.x + 116, ncEditorData.anchor01.y + 272, 120, 16 }, "Gravitation", TextFormat("%0.2f", ncEditorData.gravitationValue), & ncEditorData.gravitationValue, -100, 100);
        GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 116, ncEditorData.anchor01.y + 296, 120, 16 }, "Timestep", TextFormat("%0.2f", ncEditorData.timestepValue), & ncEditorData.timestepValue, 1, 100);
        if (GuiDropdownBox((Rectangle) { ncEditorData.anchor01.x + 24, ncEditorData.anchor01.y + 48, 252, 24 }, "STATIC; KINEMATIC; DYNAMIC", & ncEditorData.bodyTypeActive, ncEditorData.bodyTypeEditMode)) ncEditorData.bodyTypeEditMode = !ncEditorData.bodyTypeEditMode;
        ncEditorData.reset = GuiButton((Rectangle) { ncEditorData.anchor01.x + 16, ncEditorData.anchor01.y + 400, 125, 30 }, "Reset");
        GuiToggle((Rectangle) { ncEditorData.anchor01.x + 158, ncEditorData.anchor01.y + 400, 125, 30 }, "Simulate", & ncEditorData.simulate);
    }

    DrawTexture(cursorTexture, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, WHITE);

    GuiUnlock();

}

ncBody* GetBodyIntersect(ncBody* bodies, Vector2 position)
{
    for (ncBody* body = bodies; body; body = body->next)
    {
        Vector2 screen = ConvertWorldToScreen(body->position);
        if (CheckCollisionPointCircle(position, screen, ConvertWorldToPixel(body->mass * 0.5)))
        {
            return body;
        }
    }

    return NULL;
}

void DrawLineBodyToPosition(ncBody* body, Vector2 position)
{
    Vector2 screen = ConvertWorldToScreen(body->position);
    DrawLine((int)screen.x, (int)screen.y, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, YELLOW);
}