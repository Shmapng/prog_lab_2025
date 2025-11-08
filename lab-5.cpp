#include <iostream>

// Функция для двух чисел: сумма всех цифр
int calculate(int a, int b) {
    std::cout << "isp.funkc 2x chisel" << std::endl;

    int sum = 0;
    int temp;

    temp = (a < 0) ? -a : a;
    while (temp > 0) {
        sum += temp % 10;
        temp /= 10;
    }

    temp = (b < 0) ? -b : b;
    while (temp > 0) {
        sum += temp % 10;
        temp /= 10;
    }

    return sum;
}

// Функция для трех чисел: наибольшее значение из них и 25
int calculate(int a, int b, int c) {
    std::cout << "isp. funkc naibolh iz 3x chisel i 25" << std::endl;

    int max_num = a;
    if (b > max_num) max_num = b;
    if (c > max_num) max_num = c;

    return (25 > max_num) ? 25 : max_num;
}

int main() {
    int choice;
    int num1, num2, num3;

    std::cout << "Viberete punkt (1 or 2): ";
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Vvedite 3 chisla: ";
        std::cin >> num1 >> num2 >> num3;

        // Определяем количество ненулевых чисел
        int count = 0;
        if (num1 != 0) count++;
        if (num2 != 0) count++;
        if (num3 != 0) count++;

        int result;

        if (count == 2) {
            // Находим два ненулевых числа
            if (num1 != 0 && num2 != 0) {
                result = calculate(num1, num2);
            }
            else if (num1 != 0 && num3 != 0) {
                result = calculate(num1, num3);
            }
            else {
                result = calculate(num2, num3);
            }
            std::cout << "Rezultat: " << result << std::endl;

        }
        else if (count == 3) {
            result = calculate(num1, num2, num3);
            std::cout << "Rezultat: " << result << std::endl;

        }
        else {
            std::cout << "Error: vvedeno " << count << " chisel. Nado 2 or 3 nenulevix chisla." << std::endl;
        }

    }
    else if (choice == 2) {
        std::cout << "Punkt 2 vipolnaetsa" << std::endl;

    }
    else {
        std::cout << "Neverno! Dostupni tolko punkti 1 and 2." << std::endl;
    }

    return 0;
}
