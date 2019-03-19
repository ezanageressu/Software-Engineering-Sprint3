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

class Pencil : public Production
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

    void increasePrice();
    void decreasePrice();
    void sell();
    void newRate();

    ///APM functions
    double numberofApm;
    double priceofApm;
    double rateofApm;
    void buyApm();
    void apm2000();

    double round(double var); ///Function to round number to 2 decimal places
};

#endif // PENCIL_H
