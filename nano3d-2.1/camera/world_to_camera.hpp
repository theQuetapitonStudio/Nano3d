#pragma once
#include "../vector/v3.hpp"
#include "camera.hpp"

inline Vector3 world_to_camera(const Vector3& v, const Camera cam) {
    return {
        v.x - cam.position.x,
        v.y - cam.position.y,
        v.z - cam.position.z
    };
}