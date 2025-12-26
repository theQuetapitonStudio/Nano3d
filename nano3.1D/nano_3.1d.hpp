#pragma once
#include <windows.h>
#include <vector>
#include <cmath>
#include <cstdint>

// ================= CONFIG =================
constexpr int SCREEN_W = 800;
constexpr int SCREEN_H = 600;

// ================= FRAMEBUFFER =================
inline uint32_t framebuffer[SCREEN_H][SCREEN_W];

// ================= BASIC STRUCTS =================
struct Vector2 { int x, y; };

struct Vector3 {
    float x, y, z;
};

struct Triangle {
    Vector3 p1, p2, p3;
};

struct Camera {
    Vector3 position{0,0,0};
    float fov = 400.0f;
};

struct Object3D {
    std::vector<Triangle> mesh;
    Vector3 position{0,0,0};
};

// ================= MATH =================
inline Vector3 rotateX(const Vector3& v, float a) {
    float s = sin(a), c = cos(a);
    return { v.x, v.y*c - v.z*s, v.y*s + v.z*c };
}
inline Vector3 rotateY(const Vector3& v, float a) {
    float s = sin(a), c = cos(a);
    return { v.x*c + v.z*s, v.y, -v.x*s + v.z*c };
}
inline Vector3 rotateZ(const Vector3& v, float a) {
    float s = sin(a), c = cos(a);
    return { v.x*c - v.y*s, v.x*s + v.y*c, v.z };
}

inline Vector3 world_to_camera(const Vector3& v, const Camera& c) {
    return {
        v.x - c.position.x,
        v.y - c.position.y,
        v.z - c.position.z
    };
}

// ================= BUFFER =================
inline void clear_buffer(uint32_t color = 0x00101010) {
    for (int y = 0; y < SCREEN_H; y++)
        for (int x = 0; x < SCREEN_W; x++)
            framebuffer[y][x] = color;
}

// ================= DRAW =================
inline void draw_point(int x, int y, uint32_t color) {
    if (x >= 0 && x < SCREEN_W && y >= 0 && y < SCREEN_H)
        framebuffer[y][x] = color;
}

inline void draw_line(Vector2 a, Vector2 b, uint32_t color) {
    int dx = abs(b.x - a.x);
    int dy = abs(b.y - a.y);
    int sx = a.x < b.x ? 1 : -1;
    int sy = a.y < b.y ? 1 : -1;
    int err = dx - dy;

    while (true) {
        draw_point(a.x, a.y, color);
        if (a.x == b.x && a.y == b.y) break;
        int e2 = err * 2;
        if (e2 > -dy) { err -= dy; a.x += sx; }
        if (e2 <  dx) { err += dx; a.y += sy; }
    }
}

// ================= PROJECTION =================
inline Vector2 project(const Vector3& v, const Camera& cam) {
    Vector3 cv = world_to_camera(v, cam);
    float z = cv.z + 5.0f;
    if (z <= 0.1f) return {-10000,-10000};

    return {
        int((cv.x / z) * cam.fov + SCREEN_W/2),
        int((cv.y / z) * cam.fov + SCREEN_H/2)
    };
}

// ================= TRIANGLE =================
inline void draw_triangle(const Triangle& t, const Camera& cam, uint32_t color) {
    Vector2 a = project(t.p1, cam);
    Vector2 b = project(t.p2, cam);
    Vector2 c = project(t.p3, cam);

    draw_line(a,b,color);
    draw_line(b,c,color);
    draw_line(c,a,color);
}

// ================= RENDER =================
inline void render_object(const Object3D& obj, const Camera& cam) {
    for (auto t : obj.mesh) {
        t.p1.x += obj.position.x;
        t.p1.y += obj.position.y;
        t.p1.z += obj.position.z;

        t.p2.x += obj.position.x;
        t.p2.y += obj.position.y;
        t.p2.z += obj.position.z;

        t.p3.x += obj.position.x;
        t.p3.y += obj.position.y;
        t.p3.z += obj.position.z;

        draw_triangle(t, cam, 0x00FFFFFF);
    }
}

inline void render_scene(const std::vector<Object3D>& scene, const Camera& cam) {
    clear_buffer();
    for (auto& o : scene)
        render_object(o, cam);
}

// ================= WINAPI =================
inline LRESULT CALLBACK WndProc(HWND h, UINT m, WPARAM w, LPARAM l) {
    if (m == WM_DESTROY) PostQuitMessage(0);
    return DefWindowProc(h,m,w,l);
}

inline HWND create_window(HINSTANCE hInst) {
    WNDCLASS wc{};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = L"Nano3D";
    RegisterClass(&wc);

    return CreateWindow(
        L"Nano3D",L"Nano3D GDI",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,CW_USEDEFAULT,
        SCREEN_W,SCREEN_H,
        0,0,hInst,0
    );
}

inline void present(HWND hwnd) {
    HDC hdc = GetDC(hwnd);

    BITMAPINFO bmi{};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = SCREEN_W;
    bmi.bmiHeader.biHeight = -SCREEN_H;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    StretchDIBits(
        hdc,
        0,0,SCREEN_W,SCREEN_H,
        0,0,SCREEN_W,SCREEN_H,
        framebuffer,&bmi,DIB_RGB_COLORS,SRCCOPY
    );

    ReleaseDC(hwnd, hdc);
}
