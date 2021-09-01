#pragma once
#include <optional>
#include "rt.h"

struct Pattern;

struct Material {
    Color color;
    Pattern* pattern;
    float ambient, diffuse, specular, shininess,
            reflective, transparency, refractive_index;

    Material();
    bool operator==(const Material& m) const;
};
