//
// Created by levi2 on 2026. 04. 27..
//

#ifndef MAVRENDSZER_SZEMELYVONAT_H
#define MAVRENDSZER_SZEMELYVONAT_H

#include "Vonat.h"
class Szemelyvonat :public Vonat{
    int osszKapacitas;
    int jelenlegiUtasok;
public:
    Szemelyvonat(int szam, const char* honnan, const char* hova,
                 const char* ind, const char* erk, int kap);

    void listaz() const override;
    void mentes(std::ostream& os) const override;
    /**
     * @brief Személyvonat esetén nincs fix helyfoglalás.
     * @return Mindig true-t ad vissza, ha van még szabad kapacitás.
     */
    bool helyetFoglal(int& k, int& u) override;
};


#endif //MAVRENDSZER_SZEMELYVONAT_H
