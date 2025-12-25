#pragma once
#include "../vector/v3.hpp"

inline Vector3 local_to_world(const Vector3& v, const Vector3& pos) {
    return  {
        v.x + pos.x,
        v.y + pos.y,
        v.z + pos.z
    };
}