#include "Car.h"

int main() {
    setlocale(LC_ALL, "");


    srand(time(nullptr));


    vector<string> veshchi1 = {"a", "b", "v"};
    vector<string> veshchi2 = {"v", "t", "k"};

    Avtomobil mashina1("A", "ModelA", "KuzovA", "a777aa", 100, veshchi1);
    Avtomobil mashina2("B", "ModelB", "KuzovB", "b777bb", 200, veshchi2);

    cout << "=== Mashina 1 ===";
    mashina1.pokazatInfo();
    cout << "\n=== Mashina 2 ===";
    mashina2.pokazatInfo();


    Avtomobil rezultatPlus = mashina1 + mashina2;
    cout << "\n=== Rezultat '+' ===";
    rezultatPlus.pokazatInfo();


    Avtomobil rezultatMinus = mashina1 - mashina2;
    cout << "\n=== Rezultat '-' ===";
    rezultatMinus.pokazatInfo();


    Avtomobil rezultatDelenie = mashina1 / mashina2;
    cout << "\n=== Rezultat '/' ===";
    rezultatDelenie.pokazatInfo();

    
    Avtomobil mashina3 = mashina1; 
    cout << "\n=== Kopiya mashina1 (mashina3) ===";
    mashina3.pokazatInfo();

    Avtomobil mashina4;
    mashina4 = mashina2; 
    cout << "\n=== Prisvoenie mashina2 (mashina4) ===";
    mashina4.pokazatInfo();

    return 0;
}
