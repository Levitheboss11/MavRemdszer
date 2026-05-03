//
// Created by levi2 on 2026. 04. 27..
//

#ifndef MAVRENDSZER_INTERCITY_H
#define MAVRENDSZER_INTERCITY_H

#include "Vonat.h"
/**
 * @class InterCity
 * @brief InterCity vonatokat reprezentáló osztály.
 * Összetett helyfoglalási logikát valósít meg egy dinamikus mátrix segítségével.
 */
class InterCity:public Vonat {
    bool** ulesRend; /**< Dinamikus két dimenziós tömb az ülések foglaltságának tárolására. */
    int kocsikSzama;/**< A szerelvényben lévő kocsik száma. */
    int ulesekSzama;/**< Ülések száma kocsinként. */
public:
    /**
     * @brief Konstruktor InterCity vonat létrehozásához.
     * @param szam Vonatszám.
     * @param honnan Induló állomás.
     * @param hova Célállomás.
     * @param ind Indulási idő.
     * @param erk Érkezési idő.
     * @param k Kocsik száma.
     * @param u Ülések száma kocsinként.
     */
    InterCity(int szam,const char* honnan,const char* hova,const char* ind,const char* erk, int k, int u);
    /**
     * @brief Destruktor az ulesRend mátrix felszabadításához.
     */
    ~InterCity();

    void listaz() const override;
    void mentes(std::ostream& os) const override;
    /**
     * @brief Helyfoglalás megvalósítása IC vonaton.
     * Megkeresi az első szabad helyet (kocsi, ülés).
     * @param k Ide kerül a kiosztott kocsiszám.
     * @param u Ide kerül a kiosztott ülésszám.
     * @return True, ha sikerült helyet foglalni, egyébként false.
     */
    bool helyetFoglal(int& k, int& s) override;
};


#endif //MAVRENDSZER_INTERCITY_H
