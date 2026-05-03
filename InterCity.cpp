//
// Created by levi2 on 2026. 04. 27..
//
/**
 * @file InterCity.cpp
 * @author Tóth Levente István (VK0QG4)
 * @brief Az Intercity osztály megvalósítása
 * @date 2026-04-27
 */
#include "memtrace.h"
#include "InterCity.h"

InterCity::InterCity(int szam,const char* honnan, const char* hova,const char* ind,const char* erk, int k, int u)
    : Vonat(szam, honnan, hova, ind, erk), kocsikSzama(k), ulesekSzama(u) {

    //elöször foglalás
    ulesRend = new bool*[kocsikSzama];

    //minden kocsihoz lefoglaljuk az üléseket
    for (int i = 0; i < kocsikSzama; i++) {
        ulesRend[i] = new bool[u];
        for (int j = 0; j < u; j++) {
            //kezdetben minden ülés szabad ezért false
            ulesRend[i][j] = false;
        }
    }
}

InterCity::~InterCity() {
    if (ulesRend!=nullptr) {
        //minden egyes kocsi törlése
        for (int i = 0; i < kocsikSzama; ++i) {
            delete[] ulesRend[i];
        }
        //Végül a mutatók fő tömbjét
        delete[] ulesRend;
    }

}

void InterCity::listaz() const {
    std::cout << "[" << vonatszam << "] IC: " << honnan << " -> " << hova << std::endl;
    std::cout << "   Indulas: " << indulas << " | Erkezes: " << erkezes << std::endl;

    // Számoljuk meg a szabad helyeket
    int szabad = 0;
    for (int i = 0; i < kocsikSzama; ++i) {
        for (int j = 0; j < ulesekSzama; ++j) {
            if (!ulesRend[i][j]) ++szabad;
        }
    }
    std::cout << "   Kocsik: " << kocsikSzama << ", Ulesek/kocsi: " << ulesekSzama
              << " | Szabad helyek: " << szabad << std::endl;
    std::cout << "------------------------------------------" << std::endl;
}
void InterCity::mentes(std::ostream& os) const {
    os << "I;" << vonatszam << ";" << honnan << ";" << hova << ";"
       << indulas << ";" << erkezes << ";"
       << kocsikSzama << ";" << ulesekSzama << std::endl;
    // Megjegyzés: Ha el akarod menteni a konkrét foglalásokat is,
    // azt egy külön ciklussal a sor végére teheted, de alapfeladatnál
    // elég lehet a vonat adatait menteni.
}
bool InterCity::helyetFoglal(int& k, int& s) {
    for (int i = 0; i < kocsikSzama; ++i) {
        for (int j = 0; j < ulesekSzama; ++j) {
            if (ulesRend[i][j] == false) { // Találtunk egy szabad helyet
                ulesRend[i][j] = true;    // Lefoglaljuk
                k = i + 1;                // Kocsi száma (1-től indexelve)
                s = j + 1;                // Ülés száma (1-től indexelve)
                return true;
            }
        }
    }
    return false; // Nincs több szabad hely
}