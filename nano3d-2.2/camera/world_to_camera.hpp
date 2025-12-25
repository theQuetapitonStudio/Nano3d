#pragma once
#include <cmath>
#include "../vector/v3.hpp"
#include "camera.hpp"
#include "rotate.hpp"

inline Vector3 world_to_camera(const Vector3& v, const Camera& cam)
{
    Vector3 r{
        v.x - cam.position.x,
        v.y - cam.position.y,
        v.z - cam.position.z
    };

    r = crotateZ_vec(r, -cam.rotation.z);
    r = crotateY_vec(r, -cam.rotation.y);
    r = crotateX_vec(r, -cam.rotation.x);

    return r;
}
