#include <cmath>
#include <cstdio>
#include <iostream>
#include "pencil.h"
#include "production.h"
#include "wallet.h"
#include "unistd.h"

Pencil::Pencil()
{
    this->numberofPencil = 0;
    this->priceofPencil = 1.00;
    this->rateofPencil = 1;
    this->totalnumberofPencil = 0;
    this->pencilsForUpgrade = 3000;

    this->numberofApm = 1;
    this->priceofApm = 150;
    this->rateofApm = 2;
    this->apmUpgradePrice = 50;
    this->apmFractional = 0;

    this->marketing = 0;
    this->marketingUpgradePrice = 500;
}

void Pencil::producePencil(){
    if(Production::numberofWood < .21 || Production::numberofGraphite < .20){
        throw std::system_error(std::error_code(), "Not enough resources to create a pencil, replenish to make more!");
    }
    else{
        this->numberofPencil++;
        this->totalnumberofPencil++;
        Production::decreaseWood();
        Production::decreaseGraphite();
    }
}

int Pencil::getInventory(){
    return this->numberofPencil;
}

void Pencil::increasePrice(){
	this->priceofPencil += 0.05;
}

void Pencil::decreasePrice(){
	this->priceofPencil -= 0.05;
}

/*! Function to round doubles to two decimal places */
double Pencil::round(double var)
{
    double value = (int)(var * 100 + .5);
    return (double)value / 100;
}

/*! Function to calculate rate of a pencil every 0.20 seconds */
void Pencil::newRate(){
    this->rateofPencil = round((1 / this->priceofPencil)*pow(1.1, this->marketing));
}

/*! Sell pencils (according to rate) every second   */
void Pencil::sell(){
    double currentRate = floor(this->rateofPencil * 5);

    ///Selling pencils in bulk
    if(this->numberofPencil >= currentRate ){
        Wallet::balance += currentRate * this->priceofPencil;
        for (int i = 0; i < currentRate; i++){ //Decreasing sold pencils from inventory
            this->numberofPencil--;
        }
    } /* else if (this->numberofPencil < currentRate && this->numberofPencil > 0){
      ///Selling remaining pencils which are less than demand and can't be sold in bulk
      int limit = this->numberofPencil;
      for (int i = 0; i < limit - 1; i++){
        Wallet::balance += this->priceofPencil;
        this->numberofPencil--;
      }
    }
    */

}

/*! Function to produce pencils for the APM */
void Pencil::apm2000(){
    double apmInteger;
    modf(rateofApm, &apmInteger);
  for (int i = 0; i < numberofApm; i++){
      for(int j = 0; j < int(apmInteger + apmFractional);j++){
          producePencil();
      }
      if(apmFractional>1){
          apmFractional-=1;
      }
      apmFractional += modf(rateofApm, &apmInteger);
  }
}

/*! Function to buy APM and increase its price by 10% after every purchase */
void Pencil::buyApm(){
  if (Wallet::balance < this->priceofApm){
    throw std::system_error(std::error_code(), "Not enough bank balance to buy more APM's!");
  }else{
      this->numberofApm++;
      Wallet::balance -= this->priceofApm;

      this->priceofApm = this->priceofApm + (0.10 * this->priceofApm);
      //this->rateofApm += this->rateofApm;
  }
}

void Pencil::upgradeApm(){
    Pencil::rateofApm += (Pencil::rateofApm/10);
    Intelligence::intelligenceBalance -= this->apmUpgradePrice;
    this->apmUpgradePrice = 200;
    this->pencilsForUpgrade = 5000;
}

bool Pencil::activateIntelligence(){
    if(this->totalnumberofPencil>=this->pencilsForUpgrade){
        Intelligence::intelligenceIsActive = 1;
    }
    return Intelligence::intelligenceIsActive;
}

void Pencil::upgradeMarketing(){
    Pencil::marketing += 1;
    Pencil::newRate();
    Wallet::balance -= Pencil::marketingUpgradePrice;
    Pencil::marketingUpgradePrice *= 1.1;
}

