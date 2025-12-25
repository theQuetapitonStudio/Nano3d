#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <windows.h>

#include "vector/v3.hpp"
#include "vector/v2.hpp"
#include "objects/triangle.hpp"
#include "el/createrandom_string.hpp"
#include "camera/camera.hpp"
#include "camera/world_to_camera.hpp"
#include "objects/local_to_world.hpp"
#include "objects/object3d.hpp"
#include "objects/transform_triangule.hpp"

// config
constexpr int SCREEN_W = 70;
constexpr int SCREEN_H = 40;
inline char charac = '.';

// rotate
inline Vector3 rotateX_vec(const Vector3& v, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    return { v.x, v.y * c - v.z * s, v.y * s + v.z * c };
}

inline Vector3 rotateY_vec(const Vector3& v, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    return { v.x * c + v.z * s, v.y, -v.x * s + v.z * c };
}

inline Vector3 rotateZ_vec(const Vector3& v, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    return { v.x * c - v.y * s, v.x * s + v.y * c, v.z };
}

inline void rotateX(Triangle& t, float angle) {
    t.p1 = rotateX_vec(t.p1, angle);
    t.p2 = rotateX_vec(t.p2, angle);
    t.p3 = rotateX_vec(t.p3, angle);
}

inline void rotateY(Triangle& t, float angle) {
    t.p1 = rotateY_vec(t.p1, angle);
    t.p2 = rotateY_vec(t.p2, angle);
    t.p3 = rotateY_vec(t.p3, angle);
}

inline void rotateZ(Triangle& t, float angle) {
    t.p1 = rotateZ_vec(t.p1, angle);
    t.p2 = rotateZ_vec(t.p2, angle);
    t.p3 = rotateZ_vec(t.p3, angle);
}

// buffer
inline char screen[SCREEN_H][SCREEN_W];

inline void clear_buffer()
{
    for (int y = 0; y < SCREEN_H; y++)
        for (int x = 0; x < SCREEN_W; x++)
            screen[y][x] = ' ';
}

inline void present()
{
    COORD c{ 0,0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

    for (int y = 0; y < SCREEN_H; y++)
    {
        for (int x = 0; x < SCREEN_W; x++)
            std::cout << screen[y][x];
        std::cout << '\n';
    }
}

// draw
inline void draw_point(int x, int y)
{
    if (x >= 0 && x < SCREEN_W && y >= 0 && y < SCREEN_H)
        screen[y][x] = charac;
}

inline void draw_line(Vector2 a, Vector2 b)
{
    int dx = abs(b.x - a.x);
    int dy = abs(b.y - a.y);

    int sx = (a.x < b.x) ? 1 : -1;
    int sy = (a.y < b.y) ? 1 : -1;

    int err = dx - dy;

    int x = a.x;
    int y = a.y;

    while (true)
    {
        draw_point(x, y);

        if (x == b.x && y == b.y)
            break;

        int e2 = err * 2;
        if (e2 > -dy) { err -= dy; x += sx; }
        if (e2 <  dx) { err += dx; y += sy; }
    }
}

// projection
inline Vector2 project(const Vector3& v, const Camera& mamera)
{
    Vector3 cv = world_to_camera(v, mamera);
    float z = cv.z + 5.0f;

    if (z <= 0.1f)
        return { -1000, -1000 };

    float px = (cv.x / z) * mamera.fov;
    float py = (cv.y / z) * mamera.fov;

    return {
        (int)(px + SCREEN_W / 2),
        (int)(py + SCREEN_H / 2)
    };
}

// triangle
inline void draw_triangle(const Triangle& t, char ch, const Camera& mamera)
{
    Vector2 a = project(t.p1, mamera);
    Vector2 b = project(t.p2, mamera);
    Vector2 c = project(t.p3, mamera);

    char old = charac;
    charac = ch;

    draw_line(a, b);
    draw_line(b, c);
    draw_line(c, a);

    charac = old;
}

inline char shadp()
{
    return '.';
}

// render
inline void render_object(
    const Object3D& obj,
    const Camera& cam
) {
    for (const auto& t : obj.mesh) {
        Triangle wt = transform_triangle(t, obj.position);
        char shade = shadp();
        draw_triangle(wt, shade, cam);
    }
}

inline void render_scene(
    const std::vector<Object3D>& objects,
    const Camera& cam
) {
    clear_buffer();

    for (const auto& obj : objects)
        render_object(obj, cam);

    present();
}

inline void render(const std::vector<Triangle>& tris, const Camera mamera)
{
    clear_buffer();

    for (const auto& t : tris)
    {
        char shade = shadp();
        draw_triangle(t, shade, mamera);
    }

    present();
}
