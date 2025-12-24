#include "nano_3d.hpp"

int main() {
    system("color 97");
    Triangle trangu = {
        { 1 , 1, 1},
        { 2, -3, 1},
        {-5, 2 , 3}
    };
    render({ trangu });
    system("pause >nul");
    return 0;
}