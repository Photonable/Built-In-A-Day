/*******************************************************************************************
*
*   Buit In A Day - Build your empire, conquer, explore and try not to fall like Rome.
*
*   Version: 0.0.1
*
*   By Mikhail Schmalzried
*
*   This game is built  with the Raylib game engine by Ramon Santamaria (@raysan5)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2024 Photonable LLC / www.photonable.com
********************************************************************************************/

#include <stdio.h>
#include "raylib.h"
#include "include/screens.h"

#define CLAY_IMPLEMENTATION


#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


//----------------------------------------------------------------------------------
// Shared Variables Definition (global)
// NOTE: Those variables are shared between modules through screens.h
//----------------------------------------------------------------------------------
GameScreen currentScreen = LOGO_SCREEN;
Font font = { 0 };
Music music = { 0 };
Sound fxCoin = { 0 };


//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------

// Required variables to manage screen transitions (fade-in and fade-out)
static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static GameScreen transToScreen = UNKNOWN_SCREEN;


//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void ChangeToScreen(int screen);     // Change to screen, no transition effect
static void TransitionToScreen(int screen); // Request transition to next screen
static void UpdateTransition(void);         // Update transition effect
static void DrawTransition(void);           // Draw transition effect (full-screen rectangle)
static void UpdateDrawFrame(void);          // Update and draw one frame


//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Built In A Day || 0.0.1");

    InitAudioDevice();              // Initialize audio device

    // Load global data (assets that must be available in all screens)
    //font = LoadFont("assets/fonts/PressStart2P-Regular.ttf");
    //music = LoadMusicStream("assets/music/01 - Title Screen.mp3");
    //fxCoin = LoadSound("assets/sounds/coin.wav");
    //SetMusicVolume(music, 1.0f);
    //PlayMusicStream(music);

    SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
    //MaximizeWindow();
    //ToggleFullscreen();

    // Set initial game screen
    currentScreen = LOGO_SCREEN;
    InitLogoScreen();

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
    // Unload current screen data before closing
    switch (currentScreen)
    {
        case LOGO_SCREEN: UnloadLogoScreen(); break;
        case TITLE_SCREEN: UnloadTitleScreen(); break;
        case OPTIONS_SCREEN: UnloadOptionsScreen(); break;
        case GAME_SCREEN: UnloadGameScreen(); break;
        case GAME_OVER_SCREEN: UnloadGameOverScreen(); break;
        default: break;
    }

    // Unload global data (assets that must be available in all screens)
    //UnloadFont(font);
    //UnloadMusicStream(music);
    //UnloadSound(fxCoin);

    CloseAudioDevice();             // Close audio device
    //--------------------------------------------------------------------------------------

    // De-Initialization
    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
// Change to screen, no transition effect
static void ChangeToScreen(int screen)
{
    // Unload current screen
    switch (currentScreen)
    {
        case LOGO_SCREEN: UnloadLogoScreen(); break;
        case TITLE_SCREEN: UnloadTitleScreen(); break;
        case OPTIONS_SCREEN: UnloadOptionsScreen(); break;
        case GAME_SCREEN: UnloadGameScreen(); break;
        case GAME_OVER_SCREEN: UnloadGameOverScreen(); break;
        default: break;
    }

    // Init next screen
    switch (screen)
    {
        case LOGO_SCREEN: UnloadLogoScreen(); break;
        case TITLE_SCREEN: UnloadTitleScreen(); break;
        case OPTIONS_SCREEN: UnloadOptionsScreen(); break;
        case GAME_SCREEN: UnloadGameScreen(); break;
        case GAME_OVER_SCREEN: UnloadGameOverScreen(); break;
        default: break;
    }

    currentScreen = screen;
}

// Updare transition to next screen
static void TransitionToScreen(int screen)
{
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

// Update transition effect (fade-in and fade-out)
static void UpdateTransition(void)
{
    if (!transFadeOut)
    {
        transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (transAlpha > 1.01f)
        {
            transAlpha = 1.0f;

            // Unload current screen
            switch (transFromScreen)
            {
                case LOGO_SCREEN: UnloadLogoScreen(); break;
                case TITLE_SCREEN: UnloadTitleScreen(); break;
                case OPTIONS_SCREEN: UnloadOptionsScreen(); break;
                case GAME_SCREEN: UnloadGameScreen(); break;
                case GAME_OVER_SCREEN: UnloadGameOverScreen(); break;
                default: break;
            }

            // Init next screen
            switch (transToScreen)
            {
                case LOGO_SCREEN: InitLogoScreen(); break;
                case TITLE_SCREEN: InitTitleScreen(); break;
                case OPTIONS_SCREEN: InitOptionsScreen(); break;
                case GAME_SCREEN: InitGameScreen(); break;
                case GAME_OVER_SCREEN: InitGameOverScreen(); break;
                default: break;
            }

            currentScreen = transToScreen;

            // Activate fade-out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else // Transition to fade-out logic
    {
        transAlpha -= 0.02f;

        if (transAlpha < -0.01f)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = UNKNOWN_SCREEN;
        }
    }
}

// Draw transition effect (full-screen rectangle)
static void DrawTransition(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}

// Update and draw game frame
static void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    // UpdateMusicStream(music);           // NOTE: Music keeps playing between screens

    if (!onTransition)
    {
        switch (currentScreen)
        {
            case LOGO_SCREEN:
            {
                UpdateLogoScreen();

                if (FinishLogoScreen()) TransitionToScreen(TITLE_SCREEN);
            } break;
            case TITLE_SCREEN:
            {
                UpdateTitleScreen();

                if (FinishTitleScreen() == 1) TransitionToScreen(OPTIONS_SCREEN);
                else if (FinishTitleScreen() == 2) TransitionToScreen(GAME_SCREEN);
            } break;
            case OPTIONS_SCREEN:
            {
                UpdateOptionsScreen();

                if (FinishOptionsScreen()) TransitionToScreen(TITLE_SCREEN);
            } break;
            case GAME_SCREEN:
            {
                UpdateGameScreen();

                if (FinishGameScreen() == 1) TransitionToScreen(GAME_OVER_SCREEN);
                //else if (FinishGameScreen() == 2) TransitionToScreen(TITLE_SCREEN);
            } break;
            case GAME_OVER_SCREEN:
            {
                UpdateGameOverScreen();

                if (FinishGameOverScreen() == 1) TransitionToScreen(TITLE_SCREEN);
        } break;
        default: break;
        }
    }
    else UpdateTransition();    // Update transition (fade-in and fade-out)
    //----------------------------------------------------------------------------------

    
    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (currentScreen)
        {
            case LOGO_SCREEN: DrawLogoScreen(); break;
            case TITLE_SCREEN: DrawTitleScreen(); break;
            case OPTIONS_SCREEN: DrawOptionsScreen(); break;
            case GAME_SCREEN: DrawGameScreen(); break;
            case GAME_OVER_SCREEN: DrawGameOverScreen(); break;
            default: break;
        }

        // Draw full screen rectangle (fade effect) in front of everything
        if (onTransition) DrawTransition();

        DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
