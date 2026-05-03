//
// Created by levi2 on 2026. 04. 27..
//
/**
 * @file KedvezmenyesJegy.cpp
 * @author Tóth Levente István (VK0QG4)
 * @brief A KedvezmenyesJegy osztály megvalósítása
 * @date 2026-04-27
 */
#include "memtrace.h"
#include "KedvezmenyesJegy.h"
KedvezmenyesJegy::KedvezmenyesJegy(const char* nev, int vSzam, int k, int u, const char* igSzam)
    : Jegy(nev, vSzam, k, u) {
    // Itt a char* igazolvanySzam kezelése lesz majd
    this->igazolvanySzam = nullptr;
}

KedvezmenyesJegy::~KedvezmenyesJegy() {
    // Majd itt: delete[] igazolvanySzam;
}

void KedvezmenyesJegy::listaz() const {}
void KedvezmenyesJegy::mentes(std::ostream& os) const {}