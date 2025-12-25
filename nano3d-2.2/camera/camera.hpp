#pragma once
#include "../vector/v3.hpp"

struct Camera {
    Vector3 position{0,0,0};
    Vector3 rotation{0,0,0};
    float fov = 60.0f;
};
