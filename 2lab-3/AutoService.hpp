ifndef AUTO_SERVICE_HPP
#define AUTO_SERVICE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Magnitola {
    string nazvanieModeli;
    string opisanie;
    double cena;
    

    Magnitola();
    Magnitola(string nazv, string opis, double cn);
    Magnitola(const Magnitola& other);
    

    ~Magnitola();
    
    Magnitola& operator=(const Magnitola& other);
    

    void pokazatInfo() const;
};


class Avtomasterskaya {
private:
    string adres;
    vector<Magnitola> dostupnyeMagnitoly;
    vector<Avtomobil*> prikreplennyeMashiny;
    
public:

    Avtomasterskaya();
    Avtomasterskaya(const string& adr);
    Avtomasterskaya(const Avtomasterskaya& other);
    

    ~Avtomasterskaya();
    

    Avtomasterskaya& operator=(const Avtomasterskaya& other);
    

    string poluchitAdres() const;
    vector<Magnitola> poluchitDostupnyeMagnitoly() const;
    vector<Avtomobil*> poluchitPrikreplennyeMashiny() const;
    

    void ustanovitAdres(const string& adr);
    

    void dobavitMagnitolu(const Magnitola& magnitola);
    void udalitMagnitolu(const string& nazvanie);
    void pokazatVseMagnitoly() const;
    

    void prikrepitMashinu(Avtomobil* mashina);
    void otkrepitMashinu(const string& gosNomer);
    void pokazatVseMashiny() const;
    

    bool prikruitMagnitoluKMashine(const string& gosNomerMashiny, const string& nazvanieMagnitoly);
    

    void pokazatInfo() const;
};

#endif
