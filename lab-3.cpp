#include <iostream>

int main() {
    int n, x;
    int proizv = 1;    // произведение всех подходящих чисел
    int min_chislo = 0;    // минимальное подходящее число
    int min_nom_ch = 0;    // номер минимального подходящего числа

    std::cout << "Vvedite colichestvo chisel: ";
    std::cin >> n;
    if (n <= 0) {
        std::cout << "Error!" << std::endl;
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        std::cout << "Vvedite chislo: ";
        std::cin >> x;

        if (x == 0) break;
        if (x % 10 != 3 ) continue;

        if (min_nom_ch == 0) { // если подходит число под 1 номером
            min_chislo = x;
            min_nom_ch = i;
        }
        if (x < min_chislo) {
            min_chislo = x;
            min_nom_ch = i;
        }
        proizv *= x;
    }

    if (min_nom_ch == 0) { // Если не нашли ни одного подходящего числа
        std::cout << "Net chisel na 3" << std::endl;
    }
    else {
        std::cout << "Proizvedenie: " << proizv << std::endl;
        std::cout << "Min: " << min_chislo << ", Nomer: " << min_nom_ch << std::endl;
    }

    int num, sum = 0;
    std::cout << "Vvedite chislo(... < 1000): ";
    std::cin >> num;
    if (num < 0) num = -num;

    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    std::cout << "Summa cifr: " << sum << std::endl;

    return 0;
}
