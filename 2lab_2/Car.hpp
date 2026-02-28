#ifndef CAR_HPP
#define CAR_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "AutoService.hpp"

using namespace std;

struct Magnitola;

class Avtomobil {
private:
    string marka;
    string model;
    string nomer_kuzova;
    Magnitola* magnitola;
protected:
    string gos_nomer;
    int probeg;
    vector<string> veshchiVBagazhnike;

public:
    Avtomobil();
    Avtomobil(const Avtomobil& kopiya);
    Avtomobil(string m, string mdl, string nk, string gn, int pr, vector<string> veshchi);
    ~Avtomobil();
    Avtomobil& operator=(const Avtomobil& other);
    
    string poluchitMarku() const;
    string poluchitModel() const;
    string poluchitNomerKuzova() const;
    string poluchitGosNomer() const;
    int poluchitProbeg() const;
    vector<string> poluchitVeshi() const;
    Magnitola* poluchitMagnitolu() const;
    
    void ustanovitNomerKuzova(string nk);
    void ustanovitGosNomer(string gn);
    void ustanovitProbeg(int pr);
    void ustanovitVeshi(const vector<string>& novyeVeshchi);
    void ustanovitMagnitolu(Magnitola* novaMagnitola);
    
    void pokazatInfo() const;
    void umenshitProbeg(int skolko);
    
    Avtomobil operator+(const Avtomobil& other) const;
    Avtomobil operator-(const Avtomobil& other) const;
    Avtomobil operator/(const Avtomobil& other) const;
    
    static string generirovatRandomGosNomer();
};

#endif
