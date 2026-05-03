//
// Created by levi2 on 2026. 04. 27..
//

#ifndef MAVRENDSZER_KEDVEZMENYESJEGY_H
#define MAVRENDSZER_KEDVEZMENYESJEGY_H

#include "Jegy.h"
/**
 * @class KedvezmenyesJegy
 * @brief Kedvezményes jegyet reprezentáló osztály, amely igazolványszámot is tárol.
 */
class KedvezmenyesJegy : public Jegy {
    char* igazolvanySzam; /**< A kedvezményre jogosító igazolvány száma. */
public:
    KedvezmenyesJegy(const char* nev, Vonat* v, int k, int u, const char* igSzam);

    void listaz() const override;
    void mentes(std::ostream& os) const override;
    /**
         * @brief Destruktor az igazolványszám felszabadításához.
    */
    ~KedvezmenyesJegy() override;
};


#endif //MAVRENDSZER_KEDVEZMENYESJEGY_H
