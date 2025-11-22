#include <iostream>
#include <cfloat>

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

int calculate(int a, int b, int c) {
    std::cout << "isp. funkc naibolh iz 3x chisel i 25" << std::endl;

    int max_num = a;
    if (b > max_num) max_num = b;
    if (c > max_num) max_num = c;

    return (25 > max_num) ? 25 : max_num;
}

void osnFunkc() {
    unsigned char H;
    unsigned short A;
    unsigned short B;
    float S;

    std::cout << "H : ";
    std::cin >> H;
    std::cout << "A: ";
    std::cin >> A;
    std::cout << "B: ";
    std::cin >> B;

    int maUC = (1 << (sizeof(H) * 8)) - 1;
    int maUS = (1 << (sizeof(A) * 8)) - 1;

    std::cout << "unsigned char takes " << sizeof(H) << " bytes. Min=0 Max=" << maUC << std::endl;
    std::cout << "unsigned short takes " << sizeof(A) << " bytes. Min=0 Max=" << maUS << std::endl;
    std::cout << "float takes " << sizeof(S) << " bytes. Min=" << FLT_MIN << " Max=" << FLT_MAX << std::endl;

    S = (A + B) * H / 2.0f;
    std::cout << "\nRezultat (Tip float): " << S << std::endl;
}

int main() {
    int choice;
    int num1, num2, num3;

    std::cout << "Viberete punkt (1 or 2): ";
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Vvedite 3 chisla: ";
        std::cin >> num1 >> num2 >> num3;

        int count = 0;
        if (num1 != 0) count++;
        if (num2 != 0) count++;
        if (num3 != 0) count++;

        int result;

        if (count == 2) {
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
        osnFunkc();  

    }
    else {
        std::cout << "Neverno! Dostupni tolko punkti 1 and 2." << std::endl;
    }

    return 0;
}
