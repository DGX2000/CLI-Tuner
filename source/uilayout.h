#ifndef UILAYOUT_H
#define UILAYOUT_H

namespace LAYOUT::WIDTH
{
constexpr float SLIDING_BAND = 0.25F;
constexpr float SLIDING_BAND_WINDOW = SLIDING_BAND;

constexpr float OPTIONS_MENU_BOOKMARK = 0.2F;
constexpr float OPTIONS_MENU = 0.75;

constexpr float VOLUME_INDICATOR = 0.05F;
}

namespace LAYOUT::HEIGHT
{
constexpr float SLIDING_BAND = 1.0F;
constexpr float SLIDING_BAND_WINDOW = 0.15F;

constexpr float OPTIONS_MENU_BOOKMARK = 0.05F;
constexpr float OPTIONS_MENU = 1.0F;

constexpr float VOLUME_INDICATOR = 0.05F;
}

namespace LAYOUT::XOFFSET
{
constexpr float SLIDING_BAND = 0.1F;
constexpr float SLIDING_BAND_WINDOW = 0.1F;

constexpr float OPTIONS_MENU_BOOKMARK = 0.8F;
constexpr float OPTIONS_MENU = 1.0F;

constexpr float VOLUME_INDICATOR = 0.825F;
}

namespace LAYOUT::YOFFSET
{
constexpr float SLIDING_BAND = 0.0F;
constexpr float SLIDING_BAND_WINDOW =
        0.5F*LAYOUT::HEIGHT::SLIDING_BAND - 0.5F*LAYOUT::HEIGHT::SLIDING_BAND_WINDOW;

constexpr float OPTIONS_MENU_BOOKMARK = 0.9F;
constexpr float OPTIONS_MENU = 0.0F;

constexpr float VOLUME_INDICATOR = 0.905F;
}

namespace LAYOUT::OUTLINE_THICKNESS
{
constexpr float SLIDING_BAND = 2.0F;
constexpr float SLIDING_BAND_WINDOW = 8.0F;
constexpr float OPTIONS_MENU = 0.0F;
}

#endif // UILAYOUT_H
