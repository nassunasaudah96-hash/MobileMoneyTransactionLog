#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

struct Transaction
{
    int transactionId;
    std::string phoneNumber;
    std::string type;
    double amount;
    std::string dateTime;
    std::string status;
};

#endif