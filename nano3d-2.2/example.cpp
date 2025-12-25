#include "nano_3d.hpp"

std::vector<Triangle> create_cube()
{
    return {
        // frente
        {{-1,-1, 1}, { 1,-1, 1}, { 1,-1, 1}},
        {{ 1,-1, 1}, { 1, 1, 1}, { 1, 1, 1}},
        {{ 1, 1, 1}, {-1, 1, 1}, {-1, 1, 1}},
        {{-1, 1, 1}, {-1,-1, 1}, {-1,-1, 1}},

        // trás
        {{-1,-1,-1}, { 1,-1,-1}, { 1,-1,-1}},
        {{ 1,-1,-1}, { 1, 1,-1}, { 1, 1,-1}},
        {{ 1, 1,-1}, {-1, 1,-1}, {-1, 1,-1}},
        {{-1, 1,-1}, {-1,-1,-1}, {-1,-1,-1}},

        // liga frente e trás
        {{-1,-1,-1}, {-1,-1, 1}, {-1,-1, 1}},
        {{ 1,-1,-1}, { 1,-1, 1}, { 1,-1, 1}},
        {{ 1, 1,-1}, { 1, 1, 1}, { 1, 1, 1}},
        {{-1, 1,-1}, {-1, 1, 1}, {-1, 1, 1}},
    };
}


int main() {
    system("color 17");
    Camera mycamera;

    Object3D mycube;
    mycube.position = { 0,0,5};
    mycube.mesh = create_cube();

    render({ mycube.mesh }, mycamera);
    while (true) {
        if (GetAsyncKeyState('W') && 0x8000) {
            mycamera.position.z++;
            render({ mycube.mesh }, mycamera);
        }
        if (GetAsyncKeyState('S') && 0x8000) {
            mycamera.position.z--;
            render({ mycube.mesh }, mycamera);
        }
        if (GetAsyncKeyState('A') && 0x8000) {
            mycamera.position.x++;
            render({ mycube.mesh }, mycamera);
        }
        if (GetAsyncKeyState('D')) {
            mycamera.position.x--;
            render({ mycube.mesh }, mycamera);
        }
        Sleep(5);
    }
    system("pause >nul");
    return 0;
}