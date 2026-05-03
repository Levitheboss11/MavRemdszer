//
// Created by levi2 on 2026. 04. 27..
//

#ifndef MAVRENDSZER_JEGY_H
#define MAVRENDSZER_JEGY_H

#include <iostream>
/**
 * @class Jegy
 * @brief Absztrakt alaposztály a különböző jegytípusok kezeléséhez.
 */
class Jegy {
protected:
    char* utasNev;/**< Az utas neve. */
    int vonatszam;/**< A vonatszám, amire a jegy szól. */
    int kocsi;/**< Kiosztott kocsiszám. */
    int ules;/**< Kiosztott ülésszám. */
public:
    /**
     * @brief Konstruktor jegy létrehozásához.
     * @param nev Utas neve.
     * @param vSzam Vonatszám.
     * @param k Kocsiszám.
     * @param u Ülésszám.
     */
    Jegy(const char* nev, int vSzam, int k, int u);

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
};


#endif //MAVRENDSZER_JEGY_H
