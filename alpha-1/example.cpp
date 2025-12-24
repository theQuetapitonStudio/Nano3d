#include "nano_3d.hpp"

int main() {
    Triangle tru1 = {
        {-1, -1, 2},
        {1, 1, 2},
        {0,  -5, 2}
    };

    Triangle tru2 = {
        {-1, -1, 2},
        {1, -2, 2},
        {9,  -5, -2}
    };

    Triangle tru3 = {
        {-1, -1, 2},
        {-4, -2, 5},
        {-1,  -5, 2}
    };

    std::string escolha;

    std::cout << "Selecione um ponto de partida\n1. triangulo1\n2. triangulo2\n3. triangulo 3\n";

    std::cin >> escolha;

    if (escolha[0] == '1') {
        while (true) {
            render({ tru1 });
            Sleep(16);
        }
    } else if (escolha[0] == '2') {
        while (true) {
            render({ tru2 });
            Sleep(16);
        }
    } else if (escolha[0] == '3') {
        while (true) {
            render({ tru3 });
            Sleep(16);
        }
    }
}