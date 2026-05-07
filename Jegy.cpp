//
// Created by levi2 on 2026. 04. 27..
//
#include <iostream>
#include <cstring>
#include "memtrace.h"
#include "Jegy.h"
/**
 * @file Jegy.cpp
 * @author Tóth Levente István (VK0QG4)
 * @brief A jegy osztály megvalósítása
 * @date 2026-04-27
 */

Jegy::Jegy(const char* nev, Vonat* v, int k, int u)
    : vonat(v), kocsi(k), ules(u) {

    if (nev) {
        this->utasNev = new char[strlen(nev) + 1];
        strcpy(this->utasNev, nev);
    } else {
        this->utasNev = nullptr;
    }
}

Jegy::~Jegy() {
    delete[] utasNev;
}
bool Jegy::operator==(const Jegy& masik) const {
    // Vonatszám ellenőrzése (mutatón keresztül)
    if (this->vonat->getVonatszam() != masik.vonat->getVonatszam()) {
        return false;
    }

    // Kocsi és az ülés ellenőrzése
    if (this->kocsi != masik.kocsi || this->ules != masik.ules) {
        return false;
    }

    // Név ellenőrzése (strcmp-vel)
    if (strcmp(this->utasNev, masik.utasNev) != 0) {
        return false;
    }

    return true; // Ha minden egyezik
}