#include <iostream>
#include "MavRendszer.h"
/**
 * @file main.cpp
 * @author Tóth Levente István (VK0QG4)
 * @brief main
 * @date 2026-04-27
 */
#include "memtrace.h"
int main() {
    MavRendszer rendszer;

    std::cout << "MAV Jegyrendszer Skeleton" << std::endl;

    // Meghívjuk a funkciókat (még üresek, de léteznek)
    rendszer.betoltes();
    rendszer.menetrendListazas();

    // menüpont szimuláláció
    int valasztas = 0;
    if (valasztas == 5) { // Soha nem fut le, de a fordító látja a hívást
        rendszer.ujVonat();
        rendszer.jegyKiadas();
    }

    rendszer.mentes();

    return 0;
}
