#include "Car.hpp"
#include "AutoService.hpp"
#include <iostream>
#include <vector>

using namespace std;

void otsenka() {
    cout << "\n--- ocenka raboty ---" << endl;
    cout << "interes: ∞/10" << endl;
    cout << "napolnennost: 1000/10" << endl;
    cout << "slozhnost: 777/10" << endl;
}

int main() {
    setlocale(LC_ALL, "");
    srand(time(nullptr));
    
    cout << "laboratornaya 3" << endl;
    
    cout << "\n--- mashiny ---" << endl;
    vector<string> vesh1 = {"aptechka", "ognetushitel", "zapaska"};
    vector<string> vesh2 = {"zaryadka", "magnitola", "buket"};
    vector<string> vesh3 = {"zont", "ochki", "karta"};
    
    Avtomobil m1("Toyota", "Camry", "JTDBE32K123456789", "A123BC", 45000, vesh1);
    Avtomobil m2("BMW", "X5", "WBA1234567890ABC", "B456CD", 32000, vesh2);
    Avtomobil m3("Lada", "Vesta", "XTA1234567890XYZ", "C789EF", 15000, vesh3);
    
    cout << "\n--- masterskaya ---" << endl;
    Avtomasterskaya ms("ul. lenina, 15, moskva");
    
    cout << "\n--- magnitoly ---" << endl;
    Magnitola mg1("Pioneer DEH-80PRS", "CD/MP3 receiver", 25990.0);
    Magnitola mg2("Sony MEX-XB120B", "digital receiver", 18490.0);
    Magnitola mg3("JVC KD-X372BT", "CD receiver", 9990.0);
    
    ms.dobavitMagnitolu(mg1);
    ms.dobavitMagnitolu(mg2);
    ms.dobavitMagnitolu(mg3);
    
    cout << "\n--- prikreplyaem mashiny ---" << endl;
    ms.prikrepitMashinu(&m1);
    ms.prikrepitMashinu(&m2);
    ms.prikrepitMashinu(&m3);
    
    ms.pokazatInfo();
    
    cout << "\n--- ustanavlivaem magnitoly ---" << endl;
    ms.prikruitMagnitoluKMashine("A123BC", "Pioneer DEH-80PRS");
    ms.prikruitMagnitoluKMashine("B456CD", "Sony MEX-XB120B");
    
    cout << "\n--- informaciya o mashinah ---" << endl;
    m1.pokazatInfo();
    m2.pokazatInfo();
    m3.pokazatInfo();
    
    cout << "\n--- oshibka ustanovki ---" << endl;
    ms.prikruitMagnitoluKMashine("C789EF", "Blaupunkt");
    
    ms.pokazatVseMagnitoly();
    
    cout << "\n--- udalyaem magnitolu ---" << endl;
    ms.udalitMagnitolu("JVC KD-X372BT");
    
    cout << "\n--- otkreplyaem mashinu ---" << endl;
    ms.otkrepitMashinu("B456CD");
    
    ms.pokazatInfo();
    
    cout << "\n--- kopirovanie ---" << endl;
    Avtomasterskaya ms2 = ms;
    ms2.ustanovitAdres("pr. mira, 30, spb");
    ms2.pokazatInfo();
    
    otsenka();
    cout << "\n=== konec ===" << endl;
    
    return 0;
}
