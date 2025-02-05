/*******************************************************************************************
*
*   raylib [core] example - Basic 3d example
*
*   Welcome to raylib!
*
*   To compile example, just press F5.
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <stdio.h>
#include "raylib.h"
#include "C:\raylib\raylib\src\raymath.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
Camera camera = { 0 };
Vector3 cubePosition = { 0 };
float moveSpeed = 0.1f;

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void);          // Update and draw one frame

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screenWidth, screenHeight, "raylib");

    camera.position = (Vector3){ 0.0f, 10.0f, 8.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    //--------------------------------------------------------------------------------------

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(120);               // Set our game to run at 120 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Update and draw game frame
static void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera(&camera, CAMERA_CUSTOM);

    Vector3 movement = { 0.0f, 0.0f, 0.0f }; // Initialize movement vector

    if (IsKeyDown(KEY_W)){
        movement.z -= 1.0f; // Move "forward"
    }
    if (IsKeyDown(KEY_S)){
        movement.z += 1.0f; // Move "backward"
    }
    if (IsKeyDown(KEY_A)){
        movement.x -= 1.0f; // Move "left"
    }
    if (IsKeyDown(KEY_D)){
        movement.x += 1.0f; // Move "right"
    }

    // Normalize the movement vector if any movement keys are pressed.
    if (movement.x != 0.0f || movement.y != 0.0f || movement.z != 0.0f)
    {
        Vector3Normalize(movement);  // Normalize the vector
    }

    if (GetMouseWheelMove() < 0){
        camera.fovy += 1.0f;
        //camera.position.y -= 1.0f;
        //camera.target.y -= 1.0f;
    }

    if (GetMouseWheelMove() > 0){
        camera.fovy -= 1.0f;
        //camera.position.y += 1.0f;
        //camera.target.y += 1.0f;
    }
    
    // Apply the movement to the camera
    camera.position.x += movement.x * moveSpeed;
    camera.position.z += movement.z * moveSpeed; //Note the use of addition and multiplication to get direction of movement right

    camera.target.x += movement.x * moveSpeed;
    camera.target.z += movement.z * moveSpeed;

    //----------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

            DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
            DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
            DrawGrid(1000, 0.5f);

        EndMode3D();

        DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);
        char text[256];
        sprintf(text, "Camera FOV: %.1f", camera.fovy);
        DrawText(text, 10, 60, 20, DARKGRAY);

        DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
