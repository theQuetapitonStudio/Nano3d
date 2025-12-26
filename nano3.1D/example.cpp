#include "nano_3.1d.hpp"
#include "cwing-remaster.hpp"

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, int)
{
    cwing::Window win;
    win.create(hInst, L"My App", 800, 600);
    win.show();

    Camera cam;
    cam.position = {0,0,0};

    Object3D cube;
    cube.mesh = {
        { 1,1,1},
        { -1, 0, -1},
        { 2, 3, 1}
    };
    std::vector<Object3D> scene = { cube };

    float angle = 0.0f;

    win.on_resize = [&](int w, int h){
        // eu nao sei mexer com isso
    };
    win.on_paint = [&](HDC hdc){
        // paint system
    };

    // FPS loop [Use Sleep(16)]
    win.on_loop = [&](){
        angle += 0.01f;
        if (GetAsyncKeyState('W') && 0x8000) {
            cam.position.z++;
        }
        if (GetAsyncKeyState('S') && 0x8000) {
            cam.position.z--;
        }
        if (GetAsyncKeyState('A') && 0x8000) {
            cam.position.x--;
        }
        if (GetAsyncKeyState('D') && 0x8000) {
            cam.position.x++;
        }
        render_scene(scene, cam);
        present(win.hwnd);
        Sleep(16);
    };

    // main loop
    win.loop();

    return 0;
}
