//
// Created by levi2 on 2026. 04. 27..
//

#ifndef MAVRENDSZER_JEGY_H
#define MAVRENDSZER_JEGY_H

#include <iostream>
#include "Vonat.h"
/**
 * @class Jegy
 * @brief Absztrakt alaposztály a különböző jegytípusok kezeléséhez.
 */
class Jegy {
protected:
    char* utasNev;/**< Az utas neve. */
  //  int vonatszam;/**< A vonatszám, amire a jegy szól. */
    Vonat* vonat; /**< A vonat, amire a jegy szól.(vonat szám helyett) */
    int kocsi;/**< Kiosztott kocsiszám. */
    int ules;/**< Kiosztott ülésszám. */
public:
    /**
     * @brief Konstruktor jegy létrehozásához.
     * @param nev Utas neve.
     * @param v Vonat objektum.
     * @param k Kocsiszám.
     * @param u Ülésszám.
     */
    Jegy(const char* nev, Vonat* v, int k, int u);

    /**
         * @brief Virtuális destruktor a dinamikus adattagok és heterogén kollekció kezeléséhez.
         */
    virtual ~Jegy();
    /**
         * @brief Jegy adatainak kiírása.
         */
    virtual void listaz() const = 0;
    /**
     * @brief Jegy adatainak mentése fájlba.
     */
    virtual void mentes(std::ostream& os) const = 0;
    /**
     * @brief Jegy egyenlőség operator törléshez.
     */
    bool operator==(const Jegy& masik) const;
};


#endif //MAVRENDSZER_JEGY_H
