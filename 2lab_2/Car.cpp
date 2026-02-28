#include "Car.hpp"


static bool seed_initialized = false;

Avtomobil::Avtomobil() {
    marka = "Neizvestno";
    model = "Neizvestno";
    nomer_kuzova = "Neizvestno";
    gos_nomer = "A000AA";
    probeg = 0;
    veshchiVBagazhnike.clear();
    magnitola = nullptr; 
}

Avtomobil::Avtomobil(const Avtomobil& kopiya) {
    marka = kopiya.marka;
    model = kopiya.model;
    nomer_kuzova = kopiya.nomer_kuzova;
    gos_nomer = kopiya.gos_nomer;
    probeg = kopiya.probeg;
    veshchiVBagazhnike = kopiya.veshchiVBagazhnike;
    

    if (kopiya.magnitola != nullptr) {
        magnitola = new Magnitola(*kopiya.magnitola);
    } else {
        magnitola = nullptr;
    }
}

Avtomobil::Avtomobil(string m, string mdl, string nk, string gn, int pr, vector<string> veshchi) {
    marka = m;
    model = mdl;
    ustanovitNomerKuzova(nk);
    ustanovitGosNomer(gn);
    ustanovitProbeg(pr);
    veshchiVBagazhnike = veshchi;
    magnitola = nullptr;
}

Avtomobil::~Avtomobil() {
    veshchiVBagazhnike.clear();

    if (magnitola != nullptr) {
        delete magnitola;
        magnitola = nullptr;
    }
    cout << "Objekt " << marka << " " << model << " udalen (vector ochishchen, magnitola udalena)" << endl;
}

Avtomobil& Avtomobil::operator=(const Avtomobil& other) {
    if (this == &other)
        return *this;

    marka = other.marka;
    model = other.model;
    nomer_kuzova = other.nomer_kuzova;
    gos_nomer = other.gos_nomer;
    probeg = other.probeg;
    veshchiVBagazhnike = other.veshchiVBagazhnike;
    

    if (magnitola != nullptr) {
        delete magnitola;
        magnitola = nullptr;
    }
    

    if (other.magnitola != nullptr) {
        magnitola = new Magnitola(*other.magnitola);
    }

    return *this;
}


string Avtomobil::poluchitMarku() const { return marka; }
string Avtomobil::poluchitModel() const { return model; }
string Avtomobil::poluchitNomerKuzova() const { return nomer_kuzova; }
string Avtomobil::poluchitGosNomer() const { return gos_nomer; }
int Avtomobil::poluchitProbeg() const { return probeg; }
vector<string> Avtomobil::poluchitVeshi() const { return veshchiVBagazhnike; }
Magnitola* Avtomobil::poluchitMagnitolu() const { return magnitola; }


void Avtomobil::ustanovitNomerKuzova(string nk) {
    if (nk.length() >= 3)
        nomer_kuzova = nk;
    else
        nomer_kuzova = "Nekorrektnyi";
}

void Avtomobil::ustanovitGosNomer(string gn) {
    if (gn.length() == 6 &&
        isalpha(gn[0]) &&
        isdigit(gn[1]) &&
        isdigit(gn[2]) &&
        isdigit(gn[3]) &&
        isalpha(gn[4]) &&
        isalpha(gn[5]))
        gos_nomer = gn;
    else
        gos_nomer = "A000AA";
}

void Avtomobil::ustanovitProbeg(int pr) {
    if (pr >= 0)
        probeg = pr;
    else
        probeg = 0;
}

void Avtomobil::ustanovitVeshi(const vector<string>& novyeVeshchi) {
    veshchiVBagazhnike = novyeVeshchi;
}

void Avtomobil::ustanovitMagnitolu(Magnitola* novaMagnitola) {

    if (magnitola != nullptr) {
        delete magnitola;
    }
    

    if (novaMagnitola != nullptr) {
        magnitola = new Magnitola(*novaMagnitola);
    } else {
        magnitola = nullptr;
    }
}

void Avtomobil::pokazatInfo() const {
    cout << "\n=== Avtomobil ===" << endl;
    cout << "Marka: " << marka << endl;
    cout << "Model: " << model << endl;
    cout << "Kuzov: " << nomer_kuzova << endl;
    cout << "Gos nomer: " << gos_nomer << endl;
    cout << "Probeg: " << probeg << " km" << endl;
    cout << "Veshi v bagazhnike: ";
    if (veshchiVBagazhnike.empty())
        cout << "(pusto)";
    else {
        for (size_t i = 0; i < veshchiVBagazhnike.size(); ++i) {
            cout << veshchiVBagazhnike[i];
            if (i != veshchiVBagazhnike.size() - 1)
                cout << ", ";
        }
    }
    cout << endl;
    
    cout << "Magnitola: ";
    if (magnitola == nullptr) {
        cout << "ne ustanovlena" << endl;
    } else {
        cout << endl;
        magnitola->pokazatInfo();
    }
}

void Avtomobil::umenshitProbeg(int skolko) {
    if (skolko > 0) {
        probeg = probeg - skolko;
        if (probeg < 0) probeg = 0;
        cout << "Probeg umenshen na " << skolko << " km" << endl;
    }
}

string Avtomobil::generirovatRandomGosNomer() {
    if (!seed_initialized) {
        srand(time(nullptr));
        seed_initialized = true;
    }
    string nomer = "";
    nomer += 'A' + rand() % 26;
    for (int i = 0; i < 3; ++i) {
        nomer += '0' + rand() % 10;
    }
    nomer += 'A' + rand() % 26;
    nomer += 'A' + rand() % 26;
    return nomer;
}

Avtomobil Avtomobil::operator+(const Avtomobil& other) const {
    string novayaMarka = (rand() % 2 == 0) ? this->marka : other.marka;
    string novyiGosNomer = generirovatRandomGosNomer();
    
    vector<string> novyeVeshi = this->veshchiVBagazhnike;
    novyeVeshi.insert(novyeVeshi.end(), other.veshchiVBagazhnike.begin(), other.veshchiVBagazhnike.end());
    
    return Avtomobil(novayaMarka, this->model, this->nomer_kuzova, novyiGosNomer, this->probeg, novyeVeshi);
}

Avtomobil Avtomobil::operator-(const Avtomobil& other) const {
    string novayaMarka = (rand() % 2 == 0) ? this->marka : other.marka;
    string novyiGosNomer = generirovatRandomGosNomer();
    
    vector<string> unikalnye;
    
    for (const string& v : this->veshchiVBagazhnike) {
        bool found = false;
        for (const string& ov : other.veshchiVBagazhnike) {
            if (v == ov) {
                found = true;
                break;
            }
        }
        if (!found) {
            unikalnye.push_back(v);
        }
    }
    
    for (const string& ov : other.veshchiVBagazhnike) {
        bool found = false;
        for (const string& v : this->veshchiVBagazhnike) {
            if (ov == v) {
                found = true;
                break;
            }
        }
        if (!found) {
            unikalnye.push_back(ov);
        }
    }
    
    return Avtomobil(novayaMarka, this->model, this->nomer_kuzova, novyiGosNomer, this->probeg, unikalnye);
}

Avtomobil Avtomobil::operator/(const Avtomobil& other) const {
    string novayaMarka = (rand() % 2 == 0) ? this->marka : other.marka;
    string novyiGosNomer = generirovatRandomGosNomer();
    
    vector<string> obshie;
    for (const string& v : this->veshchiVBagazhnike) {
        for (const string& ov : other.veshchiVBagazhnike) {
            if (v == ov) {
                bool already = false;
                for (const string& ob : obshie) {
                    if (ob == v) {
                        already = true;
                        break;
                    }
                }
                if (!already)
                    obshie.push_back(v);
            }
        }
    }
    
    return Avtomobil(novayaMarka, this->model, this->nomer_kuzova, novyiGosNomer, this->probeg, obshie);
}
