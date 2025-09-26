#include <iostream>         // библиотека для ввода и вывода

int main() {                 // начало
    unsigned char H;         // для высоты (1..255)   unsigned char(0 до 255) 1байт
    unsigned short A, B;      // для оснований (1..1000)  unsigned short(0 до 65536) 2байта
    unsigned int S;          // для площади   unsigned int(от 0 до много) 4байта

    std::cout << "H: ";      // водим число с клавиатуры
    int temp;
    std::cin >> temp;
    H = temp;                // вресенное хранение числа

    std::cout << "A: ";     // водим число с клавиатуры
    std::cin >> temp;
    A = temp;               // вресенное хранение числа

    std::cout << "B: ";      // водим число с клавиатуры
    std::cin >> temp;
    B = temp;                // вресенное хранение числа

    S = ((A + B) * H) / 2;    //формула площади

    std::cout << "S:" << S << std::endl;     //выводим значение площади на экран

    return 0;
}