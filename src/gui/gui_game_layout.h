/*******************************************************************************************
*
*   GameLayout v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_GAME_LAYOUT_IMPLEMENTATION
*       #include "gui_game_layout.h"
*
*       INIT: GuiGameLayoutState state = InitGuiGameLayout();
*       DRAW: GuiGameLayout(&state);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()

#ifndef GUI_GAME_LAYOUT_H
#define GUI_GAME_LAYOUT_H

typedef struct {
    bool ButtonSettingsPressed;
    bool WindowBoxSettingsActive;
    bool CheckBoxFSChecked;
    bool DropdownBoxResEditMode;
    int DropdownBoxResActive;

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiGameLayoutState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiGameLayoutState InitGuiGameLayout(void);
void GuiGameLayout(GuiGameLayoutState *state);

#ifdef __cplusplus
}
#endif

#endif // GUI_GAME_LAYOUT_H

/***********************************************************************************
*
*   GUI_GAME_LAYOUT IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_GAME_LAYOUT_IMPLEMENTATION)

#include "raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiGameLayoutState InitGuiGameLayout(void)
{
    GuiGameLayoutState state = { 0 };

    state.ButtonSettingsPressed = false;
    state.WindowBoxSettingsActive = true;
    state.CheckBoxFSChecked = false;
    state.DropdownBoxResEditMode = false;
    state.DropdownBoxResActive = 0;

    // Custom variables initialization

    return state;
}

void GuiGameLayout(GuiGameLayoutState *state)
{
    if (state->DropdownBoxResEditMode) GuiLock();

    if (state->WindowBoxSettingsActive)
    {
        state->WindowBoxSettingsActive = !GuiWindowBox((Rectangle){ 600, 264, 400, 312 }, "Settings");
        GuiCheckBox((Rectangle){ 632, 312, 24, 24 }, "Full screen", &state->CheckBoxFSChecked);
        if (GuiDropdownBox((Rectangle){ 624, 360, 120, 24 }, "1280x720;1600x900;1920x1080", &state->DropdownBoxResActive, state->DropdownBoxResEditMode)) state->DropdownBoxResEditMode = !state->DropdownBoxResEditMode;
    }
    state->ButtonSettingsPressed = GuiButton((Rectangle){ 0, 24, 96, 24 }, "Settings"); 
    
    GuiUnlock();
}

#endif // GUI_GAME_LAYOUT_IMPLEMENTATION
