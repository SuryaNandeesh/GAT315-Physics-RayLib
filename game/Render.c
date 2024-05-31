#include "render.h"
#include "raymath.h"

// Define screen size and zoom level
Vector2 ncScreenSize = { 1280, 720 }; // Screen size in pixels
float ncScreenZoom = 1.0f; // Zoom level for the screen

// Define view size in world coordinates
float ncViewSize = 25.0f;

// Function to convert screen coordinates to world coordinates
Vector2 ConvertScreenToWorld(Vector2 screen)
{
    // Calculate aspect ratio
    float ratio = ncScreenSize.x / ncScreenSize.y;

    // Calculate extents of the view in world coordinates
    Vector2 extents = (Vector2){ ncViewSize * ratio, ncViewSize };
    extents = Vector2Scale(extents, ncScreenZoom);

    // Calculate lower and upper bounds of the view
    Vector2 lower = Vector2Negate(extents);
    Vector2 upper = extents;

    // Normalize screen coordinates
    float nx = screen.x / ncScreenSize.x;
    float ny = (ncScreenSize.y - screen.y) / ncScreenSize.y;

    // Map normalized coordinates to world coordinates
    Vector2 world;
    world.x = ((1 - nx) * lower.x) + (nx * upper.x);
    world.y = ((1 - ny) * lower.y) + (ny * upper.y);

    return world;
}

// Function to convert world coordinates to screen coordinates
Vector2 ConvertWorldToScreen(Vector2 world)
{
    // Calculate aspect ratio
    float ratio = ncScreenSize.x / ncScreenSize.y;

    // Calculate extents of the view in world coordinates
    Vector2 extents = (Vector2){ ncViewSize * ratio, ncViewSize };
    extents = Vector2Scale(extents, ncScreenZoom);

    // Calculate lower and upper bounds of the view
    Vector2 lower = Vector2Negate(extents);
    Vector2 upper = extents;

    // Normalize world coordinates
    float nx = (world.x - lower.x) / (upper.x - lower.x);
    float ny = (world.y - lower.y) / (upper.y - lower.y);

    // Map normalized coordinates to screen coordinates
    Vector2 screen;
    screen.x = nx * ncScreenSize.x;
    screen.y = (1.0f - ny) * ncScreenSize.y;

    return screen;
}

// Function to convert world coordinates to pixel coordinates
float ConvertWorldToPixel(float world)
{
    // Calculate aspect ratio
    float ratio = ncScreenSize.x / ncScreenSize.y;

    // Calculate extents of the view in world coordinates
    Vector2 extents = (Vector2){ ncViewSize * ratio, ncViewSize };
    extents = Vector2Scale(extents, ncScreenZoom);

    // Normalize world coordinate
    float nx = world / extents.x;

    // Map normalized coordinate to pixel coordinate
    float pixel = nx * ncScreenSize.x;

    return pixel;
}
