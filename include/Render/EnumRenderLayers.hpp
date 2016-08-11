#ifndef ENUMRENDERLAYERS_HPP
#define ENUMRENDERLAYERS_HPP


// Use of enum instead of enum class, so we can use Layer as int
enum class RenderLayers
{
    NONE,
    BACKGROUND,
    MAIN,
    SHOES,
    WEAPON,
    UPPER_BODY,
    COUNT
};

#endif // ENUMRENDERLAYERS_HPP
