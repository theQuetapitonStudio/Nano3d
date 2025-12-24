#pragma once
#include "../vector/v3.hpp"
#include <vector>
#include <iostream>
#include "triangle.hpp"

struct Object3D {
    Vector3 position;
    std::vector<Triangle> mesh;
};