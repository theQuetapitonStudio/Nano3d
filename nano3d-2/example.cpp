#include "nano_3d.hpp"


int main() {
    Triangle trangu = {
        { 1 , 1, 1},
        { 2, -3, 1},
        {-5, 2 , 3}
    };
    while (true) {
        render({ trangu });
        trangu.p1.z++;
        trangu.p2.z++;
        trangu.p3.z++;
        Sleep(16);
    }
    system("pause >nul");
    return 0;
}