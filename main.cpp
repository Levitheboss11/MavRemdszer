#include <iostream>
#include <sstream>
#include <fstream>
#include "MavRendszer.h"
#include "InterCity.h"
#include "Szemelyvonat.h"
#include "TeljesAruJegy.h"
#include "KedvezmenyesJegy.h"
#include "gtest_lite.h"
#include "memtrace.h"

int main() {

    // ============================================================
    // 1. BLOKK: ALAP VONAT LOGIKÁK
    // ============================================================

    TEST(InterCityLogika, ElsoHelyFoglalas) {
        InterCity ic(1234, "Budapest", "Gyor", "12:00", "13:30", 2, 10);
        int kocsi = 0, ules = 0;

        EXPECT_TRUE(ic.helyetFoglal(kocsi, ules));
        EXPECT_EQ(1, kocsi);
        EXPECT_EQ(1, ules);
    } END

    TEST(SzemelyvonatLogika, AlapFoglalas) {
        Szemelyvonat szv(5555, "Budapest", "Vajta", "14:10", "15:40", 200);
        int kocsi = -1, ules = -1;

        EXPECT_TRUE(szv.helyetFoglal(kocsi, ules));
        EXPECT_EQ(0, kocsi);
        EXPECT_EQ(0, ules);
    } END

    TEST(MavRendszerLogika, VonatHozzaadas) {
        MavRendszer rendszer;
        rendszer.addVonat(new Szemelyvonat(1111, "A", "B", "00:00", "00:00", 100));

        // Ha nem száll el a destruktorban a memtrace, akkor sikeres
        EXPECT_TRUE(true);
    } END

    TEST(DefenzivKezeles, NullptrStringMasolas) {
        Szemelyvonat szv(9999, nullptr, nullptr, "00:00", "00:00", 100);
        EXPECT_EQ((void*)nullptr, (void*)szv.getHonnan());
    } END


    // ============================================================
    // 2. BLOKK: JEGYEK TESZTELÉSE
    // ============================================================

    TEST(JegyLogika, JegyEgyenlosegPozitiv) {
        Szemelyvonat szv(1234, "Budapest", "Gyor", "12:00", "13:30", 200);

        TeljesAruJegy jegy1("Kovacs Janos", &szv, 0, 0);
        TeljesAruJegy jegy2("Kovacs Janos", &szv, 0, 0);

        EXPECT_TRUE(jegy1 == jegy2);
    } END

    TEST(JegyLogika, JegyEgyenlosegNegativ) {
        Szemelyvonat szv1(1234, "Budapest", "Gyor", "12:00", "13:30", 200);
        Szemelyvonat szv2(5678, "Budapest", "Pecs", "14:00", "17:00", 150);

        TeljesAruJegy alapJegy("Kovacs Janos", &szv1, 1, 12);
        TeljesAruJegy masNev("Nagy Janos", &szv1, 1, 12);
        TeljesAruJegy masVonat("Kovacs Janos", &szv2, 1, 12);
        TeljesAruJegy masHely("Kovacs Janos", &szv1, 2, 12);

        EXPECT_FALSE(alapJegy == masNev);
        EXPECT_FALSE(alapJegy == masVonat);
        EXPECT_FALSE(alapJegy == masHely);
    } END


    // ============================================================
    // 3. BLOKK: SZERIALIZÁCIÓ / MENTÉS FORMATUMOK
    // ============================================================

    TEST(Szerializacio, VonatMentesFormatum) {
        Szemelyvonat szv(9999, "Szolnok", "Debrecen", "08:15", "09:45", 150);
        std::stringstream ss;

        szv.mentes(ss);

        std::string elvart = "S;9999;Szolnok;Debrecen;08:15;09:45;150;0\n";
        EXPECT_STREQ(elvart.c_str(), ss.str().c_str());
    } END

    TEST(Szerializacio, JegyMentesFormatum) {
        InterCity ic(1111, "Bp", "Sopron", "10:00", "13:00", 3, 40);

        std::stringstream ss1, ss2;
        TeljesAruJegy tj("Kiss Peter", &ic, 2, 15);
        KedvezmenyesJegy kj("Horvath Kata", &ic, 1, 5, "IG-883");

        tj.mentes(ss1);
        kj.mentes(ss2);

        EXPECT_STREQ("T;Kiss Peter;1111;2;15\n", ss1.str().c_str());
        EXPECT_STREQ("K;Horvath Kata;1111;1;5;IG-883\n", ss2.str().c_str());
    } END


    // ============================================================
    // 4. BLOKK: NEGATÍV / HIBAKEZELÉSI TESZTEK
    // ============================================================

    TEST(InterCityHibaKezeles, TulindexeltFoglalatBeallit) {
        InterCity ic(4444, "A", "B", "12:00", "13:00", 1, 2);

        // Manuális rossz index beállítás tesztelése (Nem szabad crasheljen)
        ic.foglalatBeallit(5, 10);

        int k = 0, u = 0;
        EXPECT_TRUE(ic.helyetFoglal(k, u));
        EXPECT_EQ(1, k);
        EXPECT_EQ(1, u);
    } END

    TEST(SzemelyvonatHibaKezeles, VonatMegtelikHiba) {
        Szemelyvonat szv(3333, "A", "B", "00:00", "01:00", 2);
        int k, u;

        EXPECT_TRUE(szv.helyetFoglal(k, u));
        EXPECT_TRUE(szv.helyetFoglal(k, u));

        // A harmadik utas már nem fér el (Negatív működésnek az ellenőrzése)
        EXPECT_FALSE(szv.helyetFoglal(k, u));
    } END

    TEST(DefenzivKezeles, OnErtekadasSajatMaganak) {
        Szemelyvonat v1(5555, "Gyor", "Bp", "05:00", "06:30", 200);

        // Önértékadás meghívása (v1 = v1)
        v1 = v1;

        EXPECT_EQ(5555, v1.getVonatszam());
    } END


    // ============================================================
    // 5. BLOKK: MÁV-RENDSZER INTEGRÁCIÓS TESZT (A fő osztálynak a tesztje)
    // ============================================================

    TEST(MavRendszerLogika, RendszerSzintuMentesTeszt) {
        MavRendszer rendszer;

        // Adunk hozzá egy vonatot és egy jegyet
        InterCity* ic = new InterCity(7777, "Pecs", "Bp", "06:00", "09:00", 2, 20);
        rendszer.addVonat(ic);
        rendszer.addJegy(new TeljesAruJegy("Mav Teszt", ic, 1, 1));

        // Meghívjuk a mentést, ami kiírja a fájlokat
        rendszer.mentes();

        // Ellenőrizzük, hogy a fájlok sikeresen létrejöttek és megnyithatók-e
        std::ifstream f1("menetrend.txt");
        EXPECT_TRUE(f1.is_open());
        f1.close();

        std::ifstream f2("jegyek.txt");
        EXPECT_TRUE(f2.is_open());
        f2.close();
    } END

    return 0;
}