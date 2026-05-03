//
// Created by levi2 on 2026. 04. 27..
//
/**
 * @file Szemelyvonat.cpp
 * @author Tóth Levente István (VK0QG4)
 * @brief A Szemelyvonat osztály megvalósítása
 * @date 2026-04-27
 */
#include "memtrace.h"
#include "Szemelyvonat.h"
#include <iostream>
// Szemelyvonat.cpp
Szemelyvonat::Szemelyvonat(int szam, const char* honnan, const char* hova,
                           const char* ind, const char* erk, int kap)
    : Vonat(szam, honnan, hova, ind, erk), osszKapacitas(kap) {
    this->jelenlegiUtasok = 0; // Kezdetben üres a vonat
}


void Szemelyvonat::listaz() const {
        //Itt majd az adatok kiírása lesz
    std::cout << "[" << vonatszam << "] Szemelyvonat: "
          << honnan << " -> " << hova << std::endl;

    std::cout << "   Indulas: " << indulas << " | Erkezes: " << erkezes << std::endl;

    std::cout << "   Szabad helyek: " << (osszKapacitas - jelenlegiUtasok)
              << " / " << osszKapacitas << std::endl;

    std::cout << "------------------------------------------" << std::endl;
}
void Szemelyvonat::mentes(std::ostream& os) const {
    os << "S;"
       << vonatszam << ";"
       << honnan << ";"
       << hova << ";"
       << indulas << ";"
       << erkezes << ";"
       << osszKapacitas << ";"
       << jelenlegiUtasok << std::endl;
}
bool Szemelyvonat::helyetFoglal(int& k, int& u) {
       if (jelenlegiUtasok < osszKapacitas) {
            jelenlegiUtasok++;
           k = 0; // Személyvonatnál 0 jelzi, hogy nincs fix hely
           u = 0;
           return true;
       }
    return false; // megtelt a vonat
}