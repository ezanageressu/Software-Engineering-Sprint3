#include <iostream>
#include "wallet.h"

Wallet::Wallet(){
	this->balance = 145.00;
}

void Wallet::setBalance(double newBalance){
	this->balance = newBalance;
}

double Wallet::getBalance(){
	return this->balance;
}
