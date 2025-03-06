#include "pch.hpp"

namespace component
{
    struct animation
    {
        Texture2D texture;
        Vector2 frameSize;
        Rectangle frameRec;
        float frameTime;
        int frameCount;
        int frameCurrent;
        float elapsedTime;
        float scale;
        bool loop;
    };
}