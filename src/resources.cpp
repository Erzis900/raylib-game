#include "resources.hpp"

namespace resources
{
    Texture2D idlewalk;
    void load()
    {
        idlewalk = LoadTexture("assets/player/idlewalk.png");
    }

    void unload()
    {
        UnloadTexture(idlewalk);
    }
}