//
// Created by levi2 on 2026. 04. 27..
//
/**
 * @file Vonat.cpp
 * @author Tóth Levente István (VK0QG4)
 * @brief A Vonat osztály megvalósítása
 * @date 2026-04-27
 */
#include "memtrace.h"
#include "Vonat.h"

#include <cstring>

Vonat::Vonat(int szam, const char* honnan, const char* hova, const char* ind, const char* erk)
    : vonatszam(szam) {

    // Minden mezőnél: hossz mérése + helyfoglalás (+1 a lezáró nullának) + másolás + ellenőrzés
    if (honnan) {
        this->honnan = new char[strlen(honnan) + 1];
        strcpy(this->honnan, honnan);
    }else{
        this->honnan = nullptr;
    }

    if (hova) {
        this->hova = new char[strlen(hova) + 1];
        strcpy(this->hova, hova);
    }else {
        this->hova = nullptr;
    }

   if (ind) {
       this->indulas = new char[strlen(ind) + 1];
       strcpy(this->indulas, ind);
   }else{
        this->indulas = nullptr;
    }
    if (erk) {
        this->erkezes = new char[strlen(erk) + 1];
        strcpy(this->erkezes, erk);

    }else {
        this->erkezes = nullptr;
    }

}
Vonat::Vonat(const Vonat& masik) {
    this->vonatszam = masik.vonatszam;

    // Minden char* mezőre: ha nem null, foglalunk újat és másolunk
    this->honnan = masik.honnan ? new char[strlen(masik.honnan) + 1] : nullptr;
    if (this->honnan) strcpy(this->honnan, masik.honnan);

    this->hova = masik.hova ? new char[strlen(masik.hova) + 1] : nullptr;
    if (this->hova) strcpy(this->hova, masik.hova);

    this->indulas = masik.indulas ? new char[strlen(masik.indulas) + 1] : nullptr;
    if (this->indulas) strcpy(this->indulas, masik.indulas);

    this->erkezes = masik.erkezes ? new char[strlen(masik.erkezes) + 1] : nullptr;
    if (this->erkezes) strcpy(this->erkezes, masik.erkezes);
}
Vonat& Vonat::operator=(const Vonat& masik) {
    if (this != &masik) { // Önértékadás elleni védelem (v1 = v1)
        // 1. Régi memória felszabadítása
        delete[] honnan;
        delete[] hova;
        delete[] indulas;
        delete[] erkezes;

        // 2. Új adatok lemásolása (mint a másoló konstruktornál)
        this->vonatszam = masik.vonatszam;
        this->honnan = masik.honnan ? new char[strlen(masik.honnan) + 1] : nullptr;
        if (this->honnan) strcpy(this->honnan, masik.honnan);
        this->hova = masik.hova ? new char[strlen(masik.hova) + 1] : nullptr;
        if (this->hova) strcpy(this->hova, masik.hova);

        this->indulas = masik.indulas ? new char[strlen(masik.indulas) + 1] : nullptr;
        if (this->indulas) strcpy(this->indulas, masik.indulas);

        this->erkezes = masik.erkezes ? new char[strlen(masik.erkezes) + 1] : nullptr;
        if (this->erkezes) strcpy(this->erkezes, masik.erkezes);
    }
    return *this;
}
Vonat::~Vonat() {
    delete[] honnan;
    delete[] hova;
    delete[] indulas;
    delete[] erkezes;
}