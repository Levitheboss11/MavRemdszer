//
// Created by levi2 on 2026. 04. 27..
//
#include "memtrace.h"
#include "Jegy.h"
/**
 * @file Jegy.cpp
 * @author Tóth Levente István (VK0QG4)
 * @brief A jegy osztály destruktora
 * @date 2026-04-27
 */
//Az ősosztály destruktora
Jegy::Jegy(const char* nev, int vSzam, int k, int u) :  vonatszam(vSzam), kocsi(k), ules(u) {
    //skeleton miatt még csak nullptr
    this->utasNev = nullptr;
}

Jegy::~Jegy() {}