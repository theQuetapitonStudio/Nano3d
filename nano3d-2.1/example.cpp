#include "nano_3d.hpp"

std::vector<Triangle> create_cube()
{
    return {

        {{-1,-1, 1}, { 1,-1, 1}, { 1, 1, 1}},
        {{-1,-1, 1}, { 1, 1, 1}, {-1, 1, 1}},

        {{-1,-1,-1}, {-1, 1,-1}, { 1, 1,-1}},
        {{-1,-1,-1}, { 1, 1,-1}, { 1,-1,-1}},

        {{-1,-1,-1}, {-1,-1, 1}, {-1, 1, 1}},
        {{-1,-1,-1}, {-1, 1, 1}, {-1, 1,-1}},

        {{ 1,-1,-1}, { 1, 1,-1}, { 1, 1, 1}},
        {{ 1,-1,-1}, { 1, 1, 1}, { 1,-1, 1}},

        {{-1, 1,-1}, {-1, 1, 1}, { 1, 1, 1}},
        {{-1, 1,-1}, { 1, 1, 1}, { 1, 1,-1}},

        {{-1,-1,-1}, { 1,-1,-1}, { 1,-1, 1}},
        {{-1,-1,-1}, { 1,-1, 1}, {-1,-1, 1}},
    };
}


int main() {
    Camera mycamera;

    Object3D mycube;
    mycube.position = { 0,0,5};
    mycube.mesh = create_cube();
    while (true) {
        render({ mycube.mesh }, mycamera);
        if (GetAsyncKeyState('W') && 0x8000) {
            mycamera.position.z++;
        }
        if (GetAsyncKeyState('S') && 0x8000) {
            mycamera.position.z--;
        }
        if (GetAsyncKeyState('A') && 0x8000) {
            mycamera.position.x++;
        }
        if (GetAsyncKeyState('D') && 0x8000) {
            mycamera.position.x--;
        }
        Sleep(60);
    }
    system("pause >nul");
    return 0;
}