/***************************************************************************************
 * 
 * Author: Mikhail Schmalzried
 * 
 * Description: Header file for the screens class.
 * 
 ***************************************************************************************/

#ifndef SCREENS_H
#define SCREENS_H


//---------------------------------------------------------------------------------------
// Types and Structures Definitions
//---------------------------------------------------------------------------------------

typedef enum {
    UNKNOWN_SCREEN = -1,
    LOGO_SCREEN = 0,
    TITLE_SCREEN = 2,
    OPTIONS_SCREEN = 3,
    GAME_SCREEN = 4,
    GAME_OVER_SCREEN = 5
} GameScreen;


//----------------------------------------------------------------------------------
// Global Variables Declaration (shared by several modules)
//----------------------------------------------------------------------------------
extern GameScreen currentScreen;
extern Font font;
extern Music music;
extern Sound fxCoin;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif


//----------------------------------------------------------------------------------
// Logo Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitLogoScreen(void);
void UpdateLogoScreen(void);
void DrawLogoScreen(void);
void UnloadLogoScreen(void);
int FinishLogoScreen(void);


//----------------------------------------------------------------------------------
// Title Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitTitleScreen(void);
void UpdateTitleScreen(void);
void DrawTitleScreen(void);
void UnloadTitleScreen(void);
int FinishTitleScreen(void);


//----------------------------------------------------------------------------------
// Options Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitOptionsScreen(void);
void UpdateOptionsScreen(void);
void DrawOptionsScreen(void);
void UnloadOptionsScreen(void);
int FinishOptionsScreen(void);


//----------------------------------------------------------------------------------
// Game Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitGameScreen(void);
void UpdateGameScreen(void);
void DrawGameScreen(void);
void UnloadGameScreen(void);
int FinishGameScreen(void);


//----------------------------------------------------------------------------------
// Game Over Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitGameOverScreen(void);
void UpdateGameOverScreen(void);
void DrawGameOverScreen(void);
void UnloadGameOverScreen(void);
int FinishGameOverScreen(void);


#endif // SCREENS_H