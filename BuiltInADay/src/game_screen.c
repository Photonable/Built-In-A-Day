#include <stdio.h>



#include "raylib.h"
#include "raymath.h"
#include "screens.h"
#include "clay.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
Vector3 cubePosition = { 0 };
Camera camera = { 0 };
float moveSpeed = 0.1f;

//----------------------------------------------------------------------------------
// Game Screen Functions Definition
//----------------------------------------------------------------------------------

// Game Screen Initialization logic
void InitGameScreen(void)
{
    // TODO: Initialize GAME screen variables here!
    framesCounter = 0;
    finishScreen = 0;

    camera.position = (Vector3){ 0.0f, 10.0f, 8.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    

}

// Game Screen Update logic
void UpdateGameScreen(void)
{
    // Update camera
    UpdateCamera(&camera, CAMERA_CUSTOM);

    Vector3 movement = { 0.0f, 0.0f, 0.0f }; // Initialize movement vector

    if (IsKeyDown(KEY_W) || GetMousePosition().y < 20){
        movement.z --; // Move "forward"
    }
    if (IsKeyDown(KEY_S) || GetMousePosition().y > GetScreenHeight() - 20){
        movement.z += 1.0f; // Move "backward"
    }
    if (IsKeyDown(KEY_A) || GetMousePosition().x < 20){
        movement.x -= 1.0f; // Move "left"
    }
    if (IsKeyDown(KEY_D) || GetMousePosition().x > GetScreenWidth() - 20){
        movement.x += 1.0f; // Move "right"
    }

    // Normalize the movement vector if any movement keys are pressed.
    if (movement.x != 0.0f || movement.y != 0.0f || movement.z != 0.0f)
    {
        Vector3Normalize(movement);  // Normalize the vector
    }

    if (GetMouseWheelMove() < 0){
        camera.fovy += 1.0f;
        if (camera.fovy > 90.0f) camera.fovy = 90.0f;
        //camera.position.y -= 1.0f;
        //camera.target.y -= 1.0f;
    }

    if (GetMouseWheelMove() > 0){
        camera.fovy -= 1.0f;
        if (camera.fovy < 5.0f) camera.fovy = 5.0f;
        //camera.position.y += 1.0f;
        //camera.target.y += 1.0f;
    }
    
    // Apply the movement to the camera
    camera.position.x += movement.x * moveSpeed;
    camera.position.z += movement.z * moveSpeed; //Note the use of addition and multiplication to get direction of movement right

    camera.target.x += movement.x * moveSpeed;
    camera.target.z += movement.z * moveSpeed;



    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        Sound(fxCoin);
    }
}

// Game Screen Draw logic
void DrawGameScreen(void)
{

    BeginMode3D(camera);

        DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
        DrawGrid(1000, 0.5f);

    EndMode3D();

    DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);
    char text[256];
    sprintf(text, "Camera FOV: %.1f", camera.fovy);
    DrawText(text, 10, 60, 20, DARKGRAY);
    char mouseText[256];
    sprintf(mouseText, "Mouse Position: (%.0f, %.0f)", GetMousePosition().x, GetMousePosition().y);
    DrawText(mouseText, 10, 80, 20, DARKGRAY);
    
}

// Game Screen Unload logic
void UnloadGameScreen(void)
{
    // TODO: Unload GAME screen variables here!
}

// Game Screen should finish?
int FinishGameScreen(void)
{
    return finishScreen;
}