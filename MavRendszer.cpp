//
// Created by levi2 on 2026. 04. 27..
//
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include  <cstdlib>
#include "memtrace.h"
#include "MavRendszer.h"
#include "Szemelyvonat.h"
#include "InterCity.h"
#include "TeljesAruJegy.h"
#include "KedvezmenyesJegy.h"
/**
 * @file MavRendszer.cpp
 * @author Tóth Levente István (VK0QG4)
 * @brief A Mavrendszer osztály megvalósítása
 * @date 2026-04-27
 */
// Segéd függvények a beolvasásokhoz
int szamotBeolvas(const char* prompt, int min = 0, int max = 1000000) {
    int szam;
    while (true) {
        if (!(std::cout << prompt)) return min; // Biztonsági kilépés
        if (std::cin >> szam && szam >= min && szam <= max) {
            return szam; // Sikeres a beolvasás és benne van a tartományban
        } else {
            if (std::cin.eof()) return min;
            std::cout << "Hiba! Kerlek adj meg egy ervenyes szamot (" << min << "-" << max << ")." << std::endl;
            std::cin.clear(); // Hibaflag törlése
            std::cin.ignore(1000, '\n'); // Maradéknak a kidobása a pufferből
        }
    }
}
// Segédfüggvény az igazolvány ellenőrzéséhez
bool ervenyesIgazolvany(const char* ig) {
    return strlen(ig) >= 3;
}

// Segédfüggvény a szövegbeolvasásához és a validációhoz
void szovegetBeolvas(const char* prompt, char* buffer, int maxLen, bool (*validator)(const char*), const char* hibaUzenet) {
    while (true) {
        std::cout << prompt;
        std::cin.getline(buffer, maxLen);
        if (validator(buffer)) break;
        std::cout << hibaUzenet << std::endl;
    }
}

bool ervenyesIdoformatum(const char* ido) {
    // Egyszerű ellenőrzés: 2026.04.27-14:30 -> ez 16 karakter
    if (strlen(ido) != 16) return false;

    // Ellenőrizzük a pontokat, kötőjelet és kettőspontot a fix helyeken
    if (ido[4] != '.' || ido[7] != '.' || ido[10] != '-' || ido[13] != ':')
        return false;

    return true;
}
//Ervenyes hely megnéző segéd fügvény
bool ervenyesNev(const char* nev) {
    int hossz = strlen(nev);
    if (hossz < 2) return false; // Ha túl rövid (pl. egy üres sor vagy csak egy betű)

    bool vanBenneBetu = false;
    for (int i = 0; i < hossz; ++i) {
        if (isalpha((unsigned char)nev[i])) {
            vanBenneBetu = true;
            break;
        }
    }
    // Ha van benne legalább egy betű, elfogadjuk (így maradhat akár a kötőjel vagy a szóköz)
    return vanBenneBetu;
}
MavRendszer::~MavRendszer() {
    // 6.4 Memória felszabadítása
    for (int i = 0; i < vonatDb; ++i) delete vonatok[i];
    delete[] vonatok;

    for (int i = 0; i < jegyDb; ++i) delete jegyek[i];
    delete[] jegyek;
}

void MavRendszer::addVonat(Vonat* v) {
    // 6.1 Dinamikus tömb bővítése algoritmus
    Vonat** ujTomb = new Vonat*[vonatDb + 1];
    for (int i = 0; i < vonatDb; ++i) {
        ujTomb[i] = vonatok[i];
    }
    ujTomb[vonatDb] = v;
    delete[] vonatok;
    vonatok = ujTomb;
    vonatDb++;
}
void MavRendszer::addJegy(Jegy* j) {
    // 6.1 Dinamikus tömb bővítése algoritmus jegyekre
    Jegy** ujTomb = new Jegy*[jegyDb + 1];
    for (int i = 0; i < jegyDb; ++i) {
        ujTomb[i] = jegyek[i];
    }
    ujTomb[jegyDb] = j;
    delete[] jegyek;
    jegyek = ujTomb;
    jegyDb++;
}
void MavRendszer::ujVonat() {
    int tipus = szamotBeolvas("Tipus (1: IC, 2: Szemely): ", 1, 2);
    int szam = szamotBeolvas("Vonatszam: ", 1, 99999);

    std::cin.ignore(1000, '\n'); // Enter takarítása

    char honnan[100], hova[100], ind[20], erk[20];

    // Az új segédfüggvénnyel intézzük az összes beolvasást:
    szovegetBeolvas("Honnan: ", honnan, 100, ervenyesNev, "Hiba! Kerlek adj meg egy ervenyes varosnevet!");
    szovegetBeolvas("Hova: ", hova, 100, ervenyesNev, "Hiba! Kerlek adj meg egy ervenyes varosnevet!");
    szovegetBeolvas("Indulas (EEEE.HH.NN-OO:PP): ", ind, 20, ervenyesIdoformatum, "Hiba! Kerlek hasznald a pontos formatumot (pl. 2026.05.01-12:00)!");
    szovegetBeolvas("Erkezes (EEEE.HH.NN-OO:PP): ", erk, 20, ervenyesIdoformatum, "Hiba! Kerlek hasznald a pontos formatumot (pl. 2026.05.01-12:00)!");

    while (strcmp(ind, erk) >= 0) {
        std::cout << "Hiba: Az erkezesnek kesobb kell lennie, mint az indulasnak!" << std::endl;
        szovegetBeolvas("Uj erkezes (EEEE.HH.NN-OO:PP): ", erk, 20, ervenyesIdoformatum, "Hiba! Kerlek hasznald a pontos formatumot!");
    }

    if (tipus == 1) {
        int k = szamotBeolvas("Kocsik szama: ", 1, 20);
        int u = szamotBeolvas("Ulesek kocsiankent: ", 1, 100);
        addVonat(new InterCity(szam, honnan, hova, ind, erk, k, u));
    } else {
        addVonat(new Szemelyvonat(szam, honnan, hova, ind, erk, 200));
    }
}
void MavRendszer::jegyKiadas() {
    std::cout << "--- Jegyvasarlas ---" << std::endl;
    int vSzam = szamotBeolvas("Adja meg a vonat szamat: ", 1, 99999);

    Vonat* kivalasztottVonat = nullptr;
    for (int i = 0; i < vonatDb; ++i) {
        if (vonatok[i]->getVonatszam() == vSzam) {
            kivalasztottVonat = vonatok[i];
            break;
        }
    }

    if (kivalasztottVonat == nullptr) {
        std::cout << "Hiba: Nem talalhato vonat ezzel a szammal!" << std::endl;
        return;
    }

    int kocsi = 0, ules = 0;
    if (!kivalasztottVonat->helyetFoglal(kocsi, ules)) {
        std::cout << "Hiba: Erre a vonatra minden hely elkelt!" << std::endl;
        return;
    }

    char nev[100];
    std::cin.ignore(1000, '\n'); // Tisztítás

    szovegetBeolvas("Utas neve: ", nev, 100, ervenyesNev, "Hiba! Kerlek adj meg egy ervenyes nevet (legalabb 2 karakter, betuket tartalmazzon)!");

    char valasz;
    do {
        std::cout << "Kedvezmenyes jegy? (i/n): ";
        std::cin >> valasz;
        valasz = tolower(valasz);
    } while (valasz != 'i' && valasz != 'n');
    std::cin.ignore(1000, '\n');

    if (valasz == 'i') {
        char igazolvany[30];
        szovegetBeolvas("Igazolvany szama: ", igazolvany, 30, ervenyesIgazolvany, "Hiba! Az igazolvanyszam tul rovid!");

        addJegy(new KedvezmenyesJegy(nev, kivalasztottVonat, kocsi, ules, igazolvany));
        std::cout << "Sikeres kedvezmenyes jegyvasarlas!" << std::endl;
    } else {
        addJegy(new TeljesAruJegy(nev, kivalasztottVonat, kocsi, ules));
        std::cout << "Sikeres teljes aru jegyvasarlas!" << std::endl;
    }

    if (kocsi > 0) {
        std::cout << "Lefoglalt hely: " << kocsi << ". kocsi, " << ules << ". ules" << std::endl;
    }
}

void MavRendszer::menetrendListazas() const {
    for (int i = 0; i < vonatDb; ++i) {
        vonatok[i]->listaz();
    }
}

void MavRendszer::jegyekListazasa() const {
    for (int i = 0; i < jegyDb; ++i) {
        jegyek[i]->listaz();
    }
}

void MavRendszer::betoltes() {
    std::ifstream fajl("menetrend.txt");
    if (!fajl.is_open()) return;

    char sor[1024]; // Egy elég nagy puffer a sor beolvasásához

    while (fajl.getline(sor, 1024)) {
        if (strlen(sor) == 0) continue;

        // A strtok "szétvágja" a sort a pontosvesszők mentén
        // Első hívás: megkapjuk a típust
        char* darab = strtok(sor, ";");
        if (!darab) continue;
        char tipus = darab[0];

        // Következő darab: vonatszám
        darab = strtok(NULL, ";");
        int szam = atoi(darab);

        // Indulási állomás
        char* honnan = strtok(NULL, ";");

        // Érkezési állomás
        char* hova = strtok(NULL, ";");

        // Indulási idő
        char* ind = strtok(NULL, ";");

        // Érkezési idő
        char* erk = strtok(NULL, ";");

        if (tipus == 'S') {
            // Személyvonat extra adata: kapacitás
            darab = strtok(NULL, ";");
            int kap = atoi(darab);

            addVonat(new Szemelyvonat(szam, honnan, hova, ind, erk, kap));
        }
        else if (tipus == 'I') {
            // InterCity extra adatai: kocsik és ülések
            darab = strtok(NULL, ";");
            int kocsik = atoi(darab);
            darab = strtok(NULL, ";");
            int ulesek = atoi(darab);

            addVonat(new InterCity(szam, honnan, hova, ind, erk, kocsik, ulesek));
        }
    }
    fajl.close();
}
void MavRendszer::jegyBetoltes() {
    std::ifstream fajl("jegyek.txt");
    if (!fajl.is_open()) return;

    char sor[1024];
    while (fajl.getline(sor, 1024)) {
        if (strlen(sor) == 0) continue;

        char* darab = strtok(sor, ";");
        if (!darab) continue;
        char tipus = darab[0];

        char* nev = strtok(NULL, ";");

        darab = strtok(NULL, ";");
        if (!darab) continue;
        int vSzam = atoi(darab);

        darab = strtok(NULL, ";");
        if (!darab) continue;
        int kocsi = atoi(darab);

        darab = strtok(NULL, ";");
        if (!darab) continue;
        int ules = atoi(darab);

        // 1. Megkeressük a vonatot
        Vonat* kivalasztottVonat = nullptr;
        for (int i = 0; i < vonatDb; ++i) {
            if (vonatok[i]->getVonatszam() == vSzam) {
                kivalasztottVonat = vonatok[i];
                break;
            }
        }

        // 2. Ha megvan a vonat, jöhet a jegy és a foglalás beállítása
        if (kivalasztottVonat != nullptr) {
            if (tipus == 'T') {
                addJegy(new TeljesAruJegy(nev, kivalasztottVonat, kocsi, ules));
            }
            else if (tipus == 'K') {
                char* igazolvany = strtok(NULL, ";");
                if (igazolvany) {
                    addJegy(new KedvezmenyesJegy(nev, kivalasztottVonat, kocsi, ules, igazolvany));
                }
            }

            // Megpróbáljuk InterCity-ként kezelni a vonatot
            InterCity* ic = dynamic_cast<InterCity*>(kivalasztottVonat);
            if (ic != nullptr) {
                // Ha ez egy IC, akkor beállítjuk a mátrixában a helyet foglaltnak
                ic->foglalatBeallit(kocsi, ules);
            }
        }
    }
    fajl.close();
}
void MavRendszer::mentes() {
    std::ofstream fajl("menetrend.txt");
    if (!fajl.is_open()) return;

    for (int i = 0; i < vonatDb; ++i) {
        vonatok[i]->mentes(fajl); // A polimorfizmus miatt a jó mentes() fut le!
    }
    fajl.close();
    std::ofstream fajl2("jegyek.txt");
    if (!fajl2.is_open()) return;
    for (int i = 0; i < jegyDb; ++i) {
        jegyek[i]->mentes(fajl2);
    }
    fajl2.close();
}