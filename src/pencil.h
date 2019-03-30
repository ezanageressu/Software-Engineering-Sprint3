/**
* @file pencil.h
* @brief this header file contains the functionalities for
* buying and selling pencil and the Auto Pencil Machine (APM).
*
*/

#ifndef PENCIL_H
#define PENCIL_H
#include "production.h"
#include "wallet.h"
#include "intelligence.h"

class Pencil : public Production, public Intelligence
{
public:
    Pencil();

    ///Pencil functions
    int getInventory();
    void producePencil();

    double priceofPencil;
    double rateofPencil;
    int numberofPencil;
    double totalnumberofPencil;
    int pencilsForUpgrade;

    void increasePrice();
    void decreasePrice();
    void sell();
    void newRate();

    ///APM functions
    double numberofApm;
    double priceofApm;
    double rateofApm;
    double apmFractional;
    int apmUpgradePrice;

    void buyApm();
    void apm2000();
    void upgradeApm();
    bool activateIntelligence();

    double round(double var); ///Function to round number to 2 decimal places

    int marketing;
    double marketingUpgradePrice;

    void upgradeMarketing();
};

#endif // PENCIL_H
