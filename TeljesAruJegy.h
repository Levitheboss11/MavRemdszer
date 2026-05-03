//
// Created by levi2 on 2026. 04. 27..
//

#ifndef MAVRENDSZER_TELJESARUJEGY_H
#define MAVRENDSZER_TELJESARUJEGY_H
#include "Jegy.h"
/**
 * @class TeljesAruJegy
 * @brief Normál, teljes árú jegyet reprezentáló osztály.
 */
class TeljesAruJegy : public Jegy {
public:
    TeljesAruJegy(const char* nev, int vSzam, int k, int u);
    void listaz() const override;
    void mentes(std::ostream& os) const override;
};


#endif //MAVRENDSZER_TELJESARUJEGY_H
