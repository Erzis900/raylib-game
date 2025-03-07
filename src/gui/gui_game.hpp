#include "gui_game_layout.h"

namespace gui
{
    void initLogic(GuiGameLayoutState *state);

    void settingsButtonLogic(GuiGameLayoutState *state);
    void FScheckboxLogic(GuiGameLayoutState *state);

    Vector2 getRes(int index);
    Vector2 getWindowPosition();
    void resDropdownLogic(GuiGameLayoutState *state);

    void handleLogic(GuiGameLayoutState *state);
}