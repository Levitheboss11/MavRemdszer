//
// Created by levi2 on 2026. 04. 27..
//
#include <iostream>
#include "memtrace.h"
#include "TeljesAruJegy.h"
/**
 * @file TeljesAruJegy.cpp
 * @author Tóth Levente István (VK0QG4)
 * @brief A TeljesAruJegy osztály megvalósítása
 * @date 2026-04-27
 */
TeljesAruJegy::TeljesAruJegy(const char* nev, Vonat* v, int k, int u)
    : Jegy(nev, v, k, u) {
}

void TeljesAruJegy::listaz() const {
    std::cout << "[TELJES ARU JEGY] Utas: " << utasNev << std::endl;
    // Itt kellett az uj Vonat* v objektum mert nem tudtam volna kiirni a vonat adatait
    std::cout << "Jarat: " << vonat->getVonatszam() << std::endl;
    if (kocsi > 0) {
        std::cout << "Hely: " << kocsi << ". kocsi, " << ules << ". ules" << std::endl;
    }
    std::cout << "---------------------------------" << std::endl;
}
void TeljesAruJegy::mentes(std::ostream& os) const {
    os << "T;" << utasNev << ";" << vonat->getVonatszam() << ";" << kocsi << ";" << ules << std::endl;
}