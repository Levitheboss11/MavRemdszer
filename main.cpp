#include <iostream>
#include "MavRendszer.h"
#include "memtrace.h"

int main() {
    MavRendszer rendszer;

    // Opcionális: Indításkor töltsük be a korábbi adatokat
    rendszer.betoltes();

    int valasztas = -1;
    while (valasztas != 0) {
        std::cout << "\n=== MAV JEGYRENDSZER ===" << std::endl;
        std::cout << "1. Uj vonat felvetele" << std::endl;
        std::cout << "2. Menetrend listazasa" << std::endl;
        std::cout << "3. Jegyvasarlas" << std::endl;
        std::cout << "4. Eladott jegyek listazasa" << std::endl;
        std::cout << "5. Mentes" << std::endl;
        std::cout << "0. Kilepes" << std::endl;
        std::cout << "Valasztas: ";

        if (!(std::cin >> valasztas)) {
            // Ha valaki betűt írna szám helyett, kitakarítjuk a puffert
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        switch (valasztas) {
            case 1:
                rendszer.ujVonat();
                break;
            case 2:
                rendszer.menetrendListazas();
                break;
            case 3:
                rendszer.jegyKiadas();
                break;
            case 4:
                rendszer.jegyekListazasa();
                break;
            case 5:
                rendszer.mentes();
                std::cout << "Adatok elmentve." << std::endl;
                break;
            case 0:
                // Kilépés előtt automatikus mentés (opcionális)
                rendszer.mentes();
                std::cout << "Viszontlatasra!" << std::endl;
                break;
            default:
                std::cout << "Ervenytelen opcio!" << std::endl;
        }
    }

    return 0;
}