//
// Created by levi2 on 2026. 04. 27..
//

#ifndef MAVRENDSZER_VONAT_H
#define MAVRENDSZER_VONAT_H

#include <iostream>
/**
 * @class Vonat
 * @brief Absztrakt alaposztály a különböző vonattípusok (IC, Személy) kezeléséhez.
 */
class Vonat {
protected:
    int vonatszam;/**< A vonat egyedi 4 jegyű azonosítója. */
    char* honnan; /**< Indulási állomás neve. */
    char* hova;/**< Cél állomás neve. */
    char* indulas; /**<  Indulási időpont (ÉÉÉÉ.HH.NN ÓÓ:PP)*/
    char* erkezes;/**<  Indulási időpont ÉÉÉÉ.HH.NN ÓÓ:PP*/
public:
    /**
     * @brief Konstruktor a vonat alap adatainak beállításához.
     * @param szam Vonatszám.
     * @param honnan Indulási állomás.
     * @param hova Érkezési állomás.
     * @param ind Indulási időpont (ÉÉÉÉ.HH.NN ÓÓ:PP).
     * @param erk Érkezési időpont (ÉÉÉÉ.HH.NN ÓÓ:PP).
     */
    Vonat(int szam, const char* honnan, const char* hova,const  char* ind, const char* erk);
    /**
    * @brief  Másoló konstruktor nem feltétlen szükséges, mivel minden vonat egyedi, de a biztonság miatt
    * @param masik Vonat referencia
    */
    Vonat(const Vonat& masik);
    /**
     * @brief Virtuális destruktor.
     * Gondoskodik a heterogén kollekcióban tárolt objektumok helyes felszabadításáról.
    */
    virtual ~Vonat() ;
    /**
    * @brief  Érték adó nem feltétlen szükséges, mivel minden vonat egyedi, de a biztonság miatt
    * @param masik Vonat referencia
    */
    Vonat& operator=(const Vonat& masik);

    int getVonatszam() const { return vonatszam; }
    char* getHonnan() const { return honnan; }
    char* getHova() const { return hova; }
    /**
     * @brief Vonat adatainak listázása a képernyőre.
     * Tiszta virtuális függvény, minden leszármazott máshogy valósítja meg.
     */
    virtual void listaz() const = 0;
    virtual void mentes(std::ostream& os) const = 0;

    virtual bool helyetFoglal(int& k, int& u) = 0;
};


#endif //MAVRENDSZER_VONAT_H
