#include "/AutoService.hpp"
#include "Car.hpp"
#include <iostream>

Magnitola::Magnitola() {
    nazvanieModeli = "neizvestnaya model";
    opisanie = "net opisaniya";
    cena = 0.0;
}

Magnitola::Magnitola(string nazv, string opis, double cn) {
    nazvanieModeli = nazv;
    opisanie = opis;
    cena = (cn >= 0) ? cn : 0.0;
}

Magnitola::Magnitola(const Magnitola& other) {
    nazvanieModeli = other.nazvanieModeli;
    opisanie = other.opisanie;
    cena = other.cena;
}

Magnitola::~Magnitola() {
    cout << "magnitola \"" << nazvanieModeli << "\" udalena" << endl;
}

Magnitola& Magnitola::operator=(const Magnitola& other) {
    if (this != &other) {
        nazvanieModeli = other.nazvanieModeli;
        opisanie = other.opisanie;
        cena = other.cena;
    }
    return *this;
}

void Magnitola::pokazatInfo() const {
    cout << "  magnitola: " << nazvanieModeli << endl;
    cout << "  opisanie: " << opisanie << endl;
    cout << "  cena: " << cena << " rub." << endl;
}

Avtomasterskaya::Avtomasterskaya() {
    adres = "neizvestnyi adres";
    dostupnyeMagnitoly.clear();
    prikreplennyeMashiny.clear();
}

Avtomasterskaya::Avtomasterskaya(const string& adr) {
    adres = adr;
    dostupnyeMagnitoly.clear();
    prikreplennyeMashiny.clear();
}

Avtomasterskaya::Avtomasterskaya(const Avtomasterskaya& other) {
    adres = other.adres;
    dostupnyeMagnitoly = other.dostupnyeMagnitoly;
    prikreplennyeMashiny = other.prikreplennyeMashiny;
}

Avtomasterskaya::~Avtomasterskaya() {
    dostupnyeMagnitoly.clear();
    prikreplennyeMashiny.clear();
    cout << "avtomasterskaya po adresu \"" << adres << "\" udalena" << endl;
}

Avtomasterskaya& Avtomasterskaya::operator=(const Avtomasterskaya& other) {
    if (this != &other) {
        adres = other.adres;
        dostupnyeMagnitoly = other.dostupnyeMagnitoly;
        prikreplennyeMashiny = other.prikreplennyeMashiny;
    }
    return *this;
}

string Avtomasterskaya::poluchitAdres() const { return adres; }
vector<Magnitola> Avtomasterskaya::poluchitDostupnyeMagnitoly() const { return dostupnyeMagnitoly; }
vector<Avtomobil*> Avtomasterskaya::poluchitPrikreplennyeMashiny() const { return prikreplennyeMashiny; }

void Avtomasterskaya::ustanovitAdres(const string& adr) { adres = adr; }

void Avtomasterskaya::dobavitMagnitolu(const Magnitola& magnitola) {
    dostupnyeMagnitoly.push_back(magnitola);
    cout << "magnitola \"" << magnitola.nazvanieModeli << "\" dobavlena v masterskuyu" << endl;
}

void Avtomasterskaya::udalitMagnitolu(const string& nazvanie) {
    for (auto it = dostupnyeMagnitoly.begin(); it != dostupnyeMagnitoly.end(); ++it) {
        if (it->nazvanieModeli == nazvanie) {
            cout << "magnitola \"" << nazvanie << "\" udalena iz masterskoi" << endl;
            dostupnyeMagnitoly.erase(it);
            return;
        }
    }
    cout << "magnitola \"" << nazvanie << "\" ne naidena v masterskoi" << endl;
}

void Avtomasterskaya::pokazatVseMagnitoly() const {
    if (dostupnyeMagnitoly.empty()) {
        cout << "v masterskoi net dostupnyh magnitol" << endl;
        return;
    }
    
    cout << "\ndostupnye magnitoly v masterskoi:" << endl;
    for (size_t i = 0; i < dostupnyeMagnitoly.size(); ++i) {
        cout << i + 1 << ". ";
        dostupnyeMagnitoly[i].pokazatInfo();
    }
}

void Avtomasterskaya::prikrepitMashinu(Avtomobil* mashina) {
    if (mashina == nullptr) {
        cout << "oshibka: ukazatel na mashinu pust" << endl;
        return;
    }
    
    for (Avtomobil* m : prikreplennyeMashiny) {
        if (m == mashina) {
            cout << "mashina " << mashina->poluchitGosNomer() << " uzhe prikreplena" << endl;
            return;
        }
    }
    
    prikreplennyeMashiny.push_back(mashina);
    cout << "mashina " << mashina->poluchitMarku() << " " 
         << mashina->poluchitGosNomer() << " prikreplena k masterskoi" << endl;
}

void Avtomasterskaya::otkrepitMashinu(const string& gosNomer) {
    for (auto it = prikreplennyeMashiny.begin(); it != prikreplennyeMashiny.end(); ++it) {
        if ((*it)->poluchitGosNomer() == gosNomer) {
            cout << "mashina " << gosNomer << " otkreplena ot masterskoi" << endl;
            prikreplennyeMashiny.erase(it);
            return;
        }
    }
    cout << "mashina s nomerom " << gosNomer << " ne naidena v masterskoi" << endl;
}

void Avtomasterskaya::pokazatVseMashiny() const {
    if (prikreplennyeMashiny.empty()) {
        cout << "k masterskoi ne prikrepleno ni odnoy mashiny" << endl;
        return;
    }
    
    cout << "\nmashiny, prikreplennye k masterskoi:" << endl;
    for (size_t i = 0; i < prikreplennyeMashiny.size(); ++i) {
        cout << i + 1 << ". ";
        cout << prikreplennyeMashiny[i]->poluchitMarku() << " " 
             << prikreplennyeMashiny[i]->poluchitModel() << " ("
             << prikreplennyeMashiny[i]->poluchitGosNomer() << ")" << endl;
    }
}

bool Avtomasterskaya::prikruitMagnitoluKMashine(const string& gosNomerMashiny, const string& nazvanieMagnitoly) {
    Avtomobil* targetMashina = nullptr;
    for (Avtomobil* m : prikreplennyeMashiny) {
        if (m->poluchitGosNomer() == gosNomerMashiny) {
            targetMashina = m;
            break;
        }
    }
    
    if (targetMashina == nullptr) {
        cout << "mashina s nomerom " << gosNomerMashiny << " ne naidena v masterskoi" << endl;
        return false;
    }
    
    Magnitola* targetMagnitola = nullptr;
    for (Magnitola& m : dostupnyeMagnitoly) {
        if (m.nazvanieModeli == nazvanieMagnitoly) {
            targetMagnitola = &m;
            break;
        }
    }
    
    if (targetMagnitola == nullptr) {
        cout << "magnitola \"" << nazvanieMagnitoly << "\" ne naidena v masterskoi" << endl;
        return false;
    }
    
    targetMashina->ustanovitMagnitolu(targetMagnitola);
    cout << "magnitola \"" << nazvanieMagnitoly << "\" ustanovlena v mashinu " 
         << gosNomerMashiny << endl;
    
    return true;
}

void Avtomasterskaya::pokazatInfo() const {
    cout << "\navtomasterskaya" << endl;
    cout << "adres: " << adres << endl;
    pokazatVseMagnitoly();
    pokazatVseMashiny();
}
