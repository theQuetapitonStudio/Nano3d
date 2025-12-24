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

// config
constexpr int SCREEN_W = 80;
constexpr int SCREEN_H = 40;
inline float fov = 60.0f;
inline char charac = '#';

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
inline Vector2 project(const Vector3& v)
{
    float z = v.z + 5.0f;

    if (z <= 0.1f)
        return { -1000, -1000 };

    float px = (v.x / z) * fov;
    float py = (v.y / z) * fov;

    return {
        (int)(px + SCREEN_W / 2),
        (int)(py + SCREEN_H / 2)
    };
}

// triangle
inline void draw_triangle(const Triangle& t, char ch)
{
    Vector2 a = project(t.p1);
    Vector2 b = project(t.p2);
    Vector2 c = project(t.p3);

    char old = charac;
    charac = ch;

    draw_line(a, b);
    draw_line(b, c);
    draw_line(c, a);

    charac = old;
}

// shader & depth
inline char shadp(const Triangle& object)
{
    float z =
        (object.p1.z +
         object.p2.z +
         object.p3.z) / 3.0f;

    if (z > 20.0f) return '.';
    if (z > 10.0f) return '!';
    if (z > 5.0f)  return '"';
    if (z > 0.5f)   return '*';
    return '#';
}

// render
inline void render(const std::vector<Triangle>& tris)
{
    clear_buffer();

    for (const auto& t : tris)
    {
        char shade = shadp(t);
        draw_triangle(t, shade);
    }

    present();
}
