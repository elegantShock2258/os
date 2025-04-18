#pragma once
#include "./colors.h"

Color AlphaBlend(Color background, Color foreground, float opacity) {
    if (opacity < 0.0f) opacity = 0.0f;
    if (opacity > 1.0f) opacity = 1.0f;

    Color blended;
    blended.r = (u8)((opacity * foreground.r) + ((1.0f - opacity) * background.r));
    blended.g = (u8)((opacity * foreground.g) + ((1.0f - opacity) * background.g));
    blended.b = (u8)((opacity * foreground.b) + ((1.0f - opacity) * background.b));

    return blended;
}