#include <iostream>

int main() {
    // unsigned char для высоты (1..255)
    unsigned char H;
    // unsigned short для оснований (1..1000)
    unsigned short A;
    unsigned short B;
    // float для площади
    float S;

    std::cout << "H: ";
    std::cin >> H;
    std::cout << "A: ";
    std::cin >> A;
    std::cout << "B: ";
    std::cin >> B;

    // Вывод названий типов и их размерности в битах
    std::cout << "\nTip: unsigned char, razmer: " << sizeof(unsigned char) * 8 << " bit\n";
    std::cout << "Tip: unsigned short, razmer: " << sizeof(unsigned short) * 8 << " bit\n";
    std::cout << "Tip: float, razmer: " << sizeof(float) * 8 << " bit\n";

    // Вычисление результата
    S = (A + B) * H / 2.0f;
    std::cout << "\nRezultat (Tip float): " << S << std::endl;

    return 0;
}
