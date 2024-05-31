#pragma once
#include "raylib.h"

typedef struct ncEditorData
{
    Vector2 anchor01;

    bool editorBoxActive;
    bool bodyTypeEditMode;

    bool simulate;
    bool reset;

    int bodyTypeActive;
    float massValue;
    float dampingValue;
    float gravityScaleValue;
    float stiffnessValue;

    float gravitationValue;
    float gravityValue;
    float timestepValue;
} ncEditorData_t;

extern ncEditorData_t ncEditorData;
extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 position);
void DrawEditor(Vector2 position);

struct ncBody* GetBodyIntersect(struct ncBody* bodies, Vector2 position);
void DrawLineBodyToPosition(struct ncBody* body, Vector2 position);