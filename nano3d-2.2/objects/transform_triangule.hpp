#pragma once
#include "triangle.hpp"
#include "local_to_world.hpp"

inline Triangle transform_triangle(const Triangle& t, const Vector3& pos) {
    return {
        local_to_world(t.p1, pos),
        local_to_world(t.p2, pos),
        local_to_world(t.p2, pos)
    };
}