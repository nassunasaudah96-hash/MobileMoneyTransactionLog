#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include "Transaction.h"
#include "SinglyLinkedList.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

bool saveTransactions(
    const SinglyLinkedList<Transaction> &list,
    const std::string &filename)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    for (int i = 0; i < list.size(); i++)
    {
        Transaction t = list.getAt(i);

        file << t.transactionId << "|"
             << t.phoneNumber << "|"
             << t.type << "|"
             << std::setprecision(15) << t.amount << "|"
             << t.dateTime << "|"
             << t.status << "\n";
    }

    return file.good();
}

bool loadTransactions(
    SinglyLinkedList<Transaction> &list,
    const std::string &filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    list.clear();

    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        std::string idText, phone, type;
        std::string amountText, dateTime, status;

        if (!std::getline(ss, idText, '|') ||
            !std::getline(ss, phone, '|') ||
            !std::getline(ss, type, '|') ||
            !std::getline(ss, amountText, '|') ||
            !std::getline(ss, dateTime, '|') ||
            !std::getline(ss, status))
        {
            continue;
        }

        try
        {
            Transaction t;

            t.transactionId = std::stoi(idText);
            t.phoneNumber = phone;
            t.type = type;
            t.amount = std::stod(amountText);
            t.dateTime = dateTime;
            t.status = status;

            if (t.transactionId <= 0 ||
                phone.empty() ||
                type.empty() ||
                t.amount <= 0 ||
                dateTime.empty() ||
                status.empty())
            {
                continue;
            }

            if (list.findIndexById(t.transactionId) != -1)
            {
                continue;
            }

            list.append(t);
        }
        catch (...)
        {
            // Ignore malformed records
        }
    }

    return true;
}

#endif