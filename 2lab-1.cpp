#include <iostream>
#include <string>

using namespace std;

class Avtomobil {
private:
    string marka;
    string model;
    string nomer_kuzova;
protected:
    string gos_nomer;
    int probeg;
public:
    Avtomobil() {
        marka = "Neizvestno";
        model = "Neizvestno";
        nomer_kuzova = "Neizvestno";
        gos_nomer = "A000AA";
        probeg = 0;
    }

    Avtomobil(const Avtomobil& kopiya) {
        marka = kopiya.marka;
        model = kopiya.model;
        nomer_kuzova = kopiya.nomer_kuzova;
        gos_nomer = kopiya.gos_nomer;
        probeg = kopiya.probeg;
    }

    Avtomobil(string m, string mdl, string nk, string gn, int pr) {
        marka = m;
        model = mdl;
        ustanovitNomerKuzova(nk);
        ustanovitGosNomer(gn);
        ustanovitProbeg(pr);
    }

    ~Avtomobil() {
        cout << "Objekt " << marka << " " << model << " udalen" << endl;
    }


    string poluchitMarku() const { return marka; }
    string poluchitModel() const { return model; }
    string poluchitNomerKuzova() const { return nomer_kuzova; }
    string poluchitGosNomer() const { return gos_nomer; }
    int poluchitProbeg() const { return probeg; }


    void ustanovitNomerKuzova(string nk) {
        if (nk.length() >= 3)
            nomer_kuzova = nk;
        else
            nomer_kuzova = "Nekorrektnyi";
    }

    void ustanovitGosNomer(string gn) {
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

    void ustanovitProbeg(int pr) {
        if (pr >= 0)
            probeg = pr;
        else
            probeg = 0;
    }


    void pokazatInfo() const {
        cout << "\n=== Avtomobil ===" << endl;
        cout << "Marka: " << marka << endl;
        cout << "Model: " << model << endl;
        cout << "Kuzov: " << nomer_kuzova << endl;
        cout << "Gos nomer: " << gos_nomer << endl;
        cout << "Probeg: " << probeg << " km" << endl;
    }

    void umenshitProbeg(int skolko) {
        if (skolko > 0) {
            probeg = probeg - skolko;
            if (probeg < 0) probeg = 0;
            cout << "Probeg umenshen na " << skolko << " km" << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "");


    Avtomobil mashina1;
    mashina1.pokazatInfo();

    Avtomobil mashina2("BMW", "F90", "WBA8E9C58JCL12345", "X777XX", 45000);
    mashina2.pokazatInfo();

    Avtomobil mashina3(mashina2);
    mashina3.pokazatInfo();


    mashina1.ustanovitGosNomer("B777OP");
    cout << "Novyi nomer: " << mashina1.poluchitGosNomer() << endl;

    mashina1.ustanovitGosNomer("XYZ123");
    cout << "Oshibochnyi nomer: " << mashina1.poluchitGosNomer() << endl;


    mashina2.pokazatInfo();
    mashina2.umenshitProbeg(15000);
    cout << "Tekushchii probeg: " << mashina2.poluchitProbeg() << " km" << endl;

    return 0;
}
