#include <iostream>

// Функция для вывода первых 8 бит и самого числа
void printBits(short x) {
    std::cout << x << " = ";
    for (int i = 7; i >= 0; --i) std::cout << ((x >> i) & 1);
    std::cout << std::endl;
}

int main() {
    // Задание 1
    short A;
    int i;
    std::cout << "A: "; std::cin >> A;
    std::cout << "i (0..7): "; std::cin >> i;
    if (i < 0 || i > 7) { std::cout << "Error i\n"; return 1; }
    printBits(A);
    int abit = (A >> i) & 1;
    if (abit == 1) {
        std::cout << "i bit = 1\n";
        for (int k = 1; k <= 3; ++k) {
            A >>= 1; printBits(A);
        }
    }
    else {
        int M;
        std::cout << "Enter M: "; std::cin >> M;
        printBits(M);
        if (M > 5)
            std::cout << "M > 5 na " << M - 5 << std::endl;
        else if (M < 5)
            std::cout << "M < 5 na " << 5 - M << std::endl;
        else
            std::cout << "M = 5" << std::endl;
    }

    // Задание 2
    int N;
    std::cout << "N (nomer dna): "; std::cin >> N;
    switch (N) {
    case 1: std::cout << "Ponidelnik\n"; break;
    case 2: std::cout << "Vtornik\n"; break;
    case 3: case 4: case 5:
        // Группировка рабочих дней
        std::cout << (N == 3 ? "Sreda" : N == 4 ? "Chetverg" : "Pyatnica") << std::endl; break;
    case 6: std::cout << "Cubbota\n"; break;
    case 7: std::cout << "Voskresenye\n"; break;
    default: std::cout << "Error! Net takogo dnya.\n";
    }
    return 0;
}
