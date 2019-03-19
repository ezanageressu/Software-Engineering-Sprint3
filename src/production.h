/**
* @file wallet.h
* @brief This header file contains functionalities to
* buy and sell wood and graphite.
*
*/

#ifndef PRODUCTION_H
#define PRODUCTION_H
#include "wallet.h"


class Production : public Wallet{

public:

    Production();

    double priceofWood;
    double priceofGraphite;

    double numberofWood;
    double numberofGraphite;

    void buyWood();
    void buyGraphite();
    bool disable_buyWood();
    bool disable_buyGraphite();
    void calculatePrices();

    void decreaseWood();
    void decreaseGraphite();

    double getWood();
    double getGraphite();
};

#endif // PRODUCTION_H
