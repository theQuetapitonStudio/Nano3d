#pragma once
#include <cmath>
#include "../vector/v3.hpp"
#include "camera.hpp"

inline Vector3 crotateX_vec(const Vector3& v, float a) {
    float s = sin(a), c = cos(a);
    return { v.x, v.y * c - v.z * s, v.y * s + v.z * c };
}

inline Vector3 crotateY_vec(const Vector3& v, float a) {
    float s = sin(a), c = cos(a);
    return { v.x * c + v.z * s, v.y, -v.x * s + v.z * c };
}

inline Vector3 crotateZ_vec(const Vector3& v, float a) {
    float s = sin(a), c = cos(a);
    return { v.x * c - v.y * s, v.x * s + v.y * c, v.z };
}

