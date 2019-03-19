/**
* @file wallet.h
* @brief This header file contains required definitions
* for Wallet. It only stores Balance which is the money
* the user has in the bank.
*/

#ifndef WALLET_H
#define WALLET_H


class Wallet{
public:
    Wallet();

    double balance;

    void setBalance(double newBalance);
    double getBalance();
};

#endif // WALLET_H
