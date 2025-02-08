#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// GameOver Screen Functions Definition
//----------------------------------------------------------------------------------

// GameOver Screen Initialization logic
void InitGameOverScreen(void)
{
    // TODO: Initialize GameOver screen variables here!
    framesCounter = 0;
    finishScreen = 0;
}

// GameOver Screen Update logic
void UpdateGameOverScreen(void)
{
    // TODO: Update GameOver screen variables here!

    // Press enter or tap to return to TITLE screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

// GameOver Screen Draw logic
void DrawGameOverScreen(void)
{
    // TODO: Draw GameOver screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);

    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "GameOver SCREEN", pos, font.baseSize*3.0f, 4, DARKBLUE);
    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
}

// GameOver Screen Unload logic
void UnloadGameOverScreen(void)
{
    // TODO: Unload GameOver screen variables here!
}

// GameOver Screen should finish?
int FinishGameOverScreen(void)
{
    return finishScreen;
}