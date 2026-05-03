//
// Created by levi2 on 2026. 04. 27..
//
/**
 * @file KedvezmenyesJegy.cpp
 * @author Tóth Levente István (VK0QG4)
 * @brief A KedvezmenyesJegy osztály megvalósítása
 * @date 2026-04-27
 */
#include <iostream>
#include <cstring>
#include "memtrace.h"
#include "KedvezmenyesJegy.h"
/**
 * @file KedvezmenyesJegy.cpp
 * @author Tóth Levente István (VK0QG4)
 * @brief KedvezmenyesJegy osztály megvalósítása
 * @date 2026-04-27
 */
KedvezmenyesJegy::KedvezmenyesJegy(const char* nev, Vonat* v, int k, int u, const char* igSzam)
    : Jegy(nev, v, k, u) {

    if (igSzam) {
        this->igazolvanySzam = new char[strlen(igSzam) + 1];
        strcpy(this->igazolvanySzam, igSzam);
    } else {
        this->igazolvanySzam = nullptr;
    }
}

KedvezmenyesJegy::~KedvezmenyesJegy() {
    //vitualis destruk miatt behivodik a ~Jegy destruktora is.
    delete[] this->igazolvanySzam;
}

void KedvezmenyesJegy::listaz() const {
    std::cout << "[KEDVEZMENYES JEGY] Utas: " << utasNev << std::endl;
    std::cout << "   Igazolvany: " << igazolvanySzam << std::endl;
    std::cout << "   Vonat: " << vonat->getVonatszam() << std::endl;
    if (kocsi > 0) {
        std::cout << "   Hely: " << kocsi << ". kocsi, " << ules << ". ules" << std::endl;
    }
    std::cout << "---------------------------------" << std::endl;
}
void KedvezmenyesJegy::mentes(std::ostream& os) const {
    // K = Kedvezményes típusazonosító
    os << "K;" << utasNev << ";" << vonat->getVonatszam() << ";"
       << kocsi << ";" << ules << ";" << igazolvanySzam << std::endl;
}