#include <iostream>
#include <string>
#include <random>


inline std::string randomString(size_t tamanho) {
    const std::string chars =
        "$#@&";

    std::random_device rd;               // entropia do sistema
    std::mt19937 gen(rd());               // Mersenne Twister
    std::uniform_int_distribution<> dist(0, chars.size() - 1);

    std::string resultado;
    resultado.reserve(tamanho);

    for (size_t i = 0; i < tamanho; i++) {
        resultado += chars[dist(gen)];
    }

    return resultado;
}
