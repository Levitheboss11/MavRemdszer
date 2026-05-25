//
// Created by levi2 on 2026. 04. 27..
//

#ifndef MAVRENDSZER_MAVRENDSZER_H
#define MAVRENDSZER_MAVRENDSZER_H

#include "Vonat.h"
#include "Jegy.h"
/**
 * @class MavRendszer
 * @brief A teljes vasúti rendszert összefogó osztály.
 * Felelős a vonatok és jegyek tárolásáért, mentéséért és a menü vezérléséért.
 */
class MavRendszer {
    Vonat** vonatok;/**< Dinamikus tömb a vonatok tárolásához (heterogén kollekció). */
    int vonatDb;/**< Tárolt vonatok száma. */
    Jegy** jegyek;/**< Dinamikus tömb a jegyek tárolásához (heterogén kollekció). */
    int jegyDb;/**< Tárolt jegyek száma. */

public:
    /**
     * @brief Konstruktor, inicializálja az üres listákat.
     */
    MavRendszer() : vonatok(nullptr), vonatDb(0), jegyek(nullptr), jegyDb(0) {}
    /**
     * @brief Destruktor, felszabadítja a heterogén kollekciókat és az összes tárolt objektumot.
     */
    ~MavRendszer();
        /**
         * @brief Adatok betöltése fájlból.
         * Megnyitja a menetrend.txt-t és a jegyek.txt-t, majd felépíti az objektumokat a memóriában.
         */
    void betoltes();
    /** @brief Adatok mentése háttértárba. */
    void mentes();
    /**
     * @brief Interaktív folyamat új vonat felvételéhez.
     * Bekéri az adatokat a felhasználótól a konzolon keresztül,
     * példányosítja a megfelelő Vonat típust, majd átadja az addVonat-nak.
     */
    void ujVonat();
    /**
     * @brief Interaktív jegyvásárlási folyamat.
     * Bekéri az útvonalat, keresi a vonatot, kezeli a helyfoglalást,
     * példányosítja a jegyet, majd átadja az addJegy-nek.
     */
    void jegyKiadas();
    /** @brief A menetrend kilistázása a képernyőre. */
    void menetrendListazas() const;
    /** @brief Az összes eladott jegy listázása. */
    void jegyekListazasa() const;

    // Segédfüggvények a dinamikus tömbökhöz
    /**
     * @brief Alacsony szintű segédfüggvény a dinamikus tömb bővítéséhez.
     * Elvégzi a memóriafoglalást, a régi mutatók másolását és a felszabadítást.
     * @param v A már létrehozott, hozzáadandó vonat mutatója.
     */
    void addVonat(Vonat* v);
    /**
     * @brief Alacsony szintű segédfüggvény a jegyek dinamikus tömbjének bővítéséhez.
     * Elvégzi a memóriakezelési lépéseket a jegyek mutatótömbjén.
     * @param j A hozzáadandó jegy mutatója.
     */
    void addJegy(Jegy* j);
    void jegyBetoltes();
    //uj private segedfuggvenyek beolvasashoz
    int szamotBeolvas(const char* prompt, int min = 0, int max = 1000000);
   static bool ervenyesIgazolvany(const char* ig);
    void szovegetBeolvas(const char* prompt, char* buffer, int maxLen, bool (*validator)(const char*), const char* hibaUzenet);
   static bool ervenyesIdoformatum(const char* ido);
   static bool ervenyesNev(const char* nev);

};


#endif //MAVRENDSZER_MAVRENDSZER_H
