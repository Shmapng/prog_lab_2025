#include <iostream>
#include <limits>


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

    // вывод тип данных на экран
    std::cout << "unsigned char takes " << sizeof(H) << " bytes. Min=" << +std::numeric_limits<unsigned char>::min()
        << " Max=" << +std::numeric_limits<unsigned char>::max() << std::endl;

    std::cout << "unsigned short takes " << sizeof(A) << " bytes. Min=" << std::numeric_limits<unsigned short>::min()
        << " Max=" << std::numeric_limits<unsigned short>::max() << std::endl;

    std::cout << "float takes " << sizeof(S) << " bytes. Min=" << FLT_MIN
        << " Max=" << FLT_MAX << std::endl;

    // Вычисление результата
    S = (A + B) * H / 2.0f;
    std::cout << "\nRezultat (Tip float): " << S << std::endl;

    return 0;
}
