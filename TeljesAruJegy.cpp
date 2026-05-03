//
// Created by levi2 on 2026. 04. 27..
//
#include "memtrace.h"
#include "TeljesAruJegy.h"
/**
 * @file TeljesAruJegy.cpp
 * @author Tóth Levente István (VK0QG4)
 * @brief A TeljesAruJegy osztály megvalósítása
 * @date 2026-04-27
 */
TeljesAruJegy::TeljesAruJegy(const char* nev, int vSzam, int k, int u)
    : Jegy(nev, vSzam, k, u) {}

void TeljesAruJegy::listaz() const {}
void TeljesAruJegy::mentes(std::ostream& os) const {}