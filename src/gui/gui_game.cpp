#include "gui_game.hpp"
#include "pch.hpp"
#include "constants.hpp"

namespace gui
{
    void initLogic(GuiGameLayoutState *state)
    {
        state->WindowBoxSettingsActive = false;
        state->DropdownBoxResActive = 1;
    }

    void settingsButtonLogic(GuiGameLayoutState *state)
    {
        if(state->ButtonSettingsPressed)
        {
            state->WindowBoxSettingsActive = !state->WindowBoxSettingsActive;
        }
    }

    Vector2 getRes(int index)
    {
        Vector2 vec;
        switch(index)
        {
            case 0:
                vec = {1280, 720};
                break;
            case 1:
                vec = {1600, 896};
                break;
            case 2:
                vec = {1920, 1080};
                break;
            default:
                break;
        }
        
        return vec;
    }

    Vector2 getWindowPosition()
    {
        int monitor = GetCurrentMonitor();
        Vector2 monitorCenter = { static_cast<float>(GetMonitorWidth(monitor)) / 2, static_cast<float>(GetMonitorHeight(monitor)) / 2 };
        Vector2 resCenter = { static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2 };

        return {monitorCenter.x - resCenter.x, monitorCenter.y - resCenter.y };
    }

    void FScheckboxLogic(GuiGameLayoutState *state)
    {
        static bool prevState = false;
        if(state->CheckBoxFSChecked && !prevState)
        {   
            ToggleBorderlessWindowed();
            // ToggleFullscreen();
            prevState = true;
        }
        else if(!state->CheckBoxFSChecked && prevState)
        {
            // ToggleFullscreen();
            ToggleBorderlessWindowed();
            Vector2 res = getRes(state->DropdownBoxResActive);
            SetWindowSize(res.x, res.y);

            Vector2 windowPos = getWindowPosition();
            SetWindowPosition(windowPos.x, windowPos.y);

            prevState = false;
        }
    }

    void resDropdownLogic(GuiGameLayoutState *state)
    {
        static int prev = -1;
        if(state->DropdownBoxResActive != prev)
        {
            prev = state->DropdownBoxResActive;

            Vector2 res = getRes(state->DropdownBoxResActive);
            SetWindowSize(res.x, res.y);

            Vector2 windowPos = getWindowPosition();
            SetWindowPosition(windowPos.x, windowPos.y);
        }
    }

    void handleLogic(GuiGameLayoutState *state)
    {
        settingsButtonLogic(state);
        FScheckboxLogic(state);
        resDropdownLogic(state);
    }
}