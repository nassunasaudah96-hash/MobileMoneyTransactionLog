#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

#include "Transaction.h"
#include "SinglyLinkedList.h"
#include "Sorting.h"
#include "Searching.h"
#include "FileHandling.h"

using namespace std;

void displayTransaction(const Transaction &t)
{
    cout << fixed << setprecision(2);

    cout << "\nTransaction ID: " << t.transactionId
         << "\nPhone Number: " << t.phoneNumber
         << "\nTransaction Type: " << t.type
         << "\nAmount: UGX " << t.amount
         << "\nDate and Time: " << t.dateTime
         << "\nStatus: " << t.status
         << "\n-----------------------------\n";
}

void displayAll(const SinglyLinkedList<Transaction> &list)
{
    if (list.isEmpty())
    {
        cout << "No transactions available.\n";
        return;
    }

    for (int i = 0; i < list.size(); i++)
    {
        displayTransaction(list.getAt(i));
    }
}

bool validType(const string &type)
{
    return type == "Deposit" ||
           type == "Withdrawal" ||
           type == "Transfer" ||
           type == "Airtime";
}

bool validStatus(const string &status)
{
    return status == "Successful" ||
           status == "Failed" ||
           status == "Pending";
}

int main()
{
    SinglyLinkedList<Transaction> transactions;

    const string filename = "transactions.txt";

    if (loadTransactions(transactions, filename))
    {
        cout << "Transaction records loaded successfully.\n";
    }
    else
    {
        cout << "No transaction file found. Starting with an empty list.\n";
    }

    int choice = -1;

    do
    {
        cout << "\n====================================\n";
        cout << "     MOBILE MONEY TRANSACTION LOG\n";
        cout << "====================================\n";
        cout << "1. Display all transactions\n";
        cout << "2. Add a transaction\n";
        cout << "3. Remove a transaction\n";
        cout << "4. Update transaction status\n";
        cout << "5. Sort by amount (Merge Sort)\n";
        cout << "6. Sort by ID (Insertion Sort)\n";
        cout << "7. Search by transaction ID\n";
        cout << "8. Save transactions\n";
        cout << "0. Save and exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number.\n";
            choice = -1;
            continue;
        }

        if (choice == 1)
        {
            displayAll(transactions);
        }

        else if (choice == 2)
        {
            Transaction t;

            cout << "Enter transaction ID: ";
            if (!(cin >> t.transactionId) || t.transactionId <= 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid transaction ID.\n";
                continue;
            }

            if (transactions.findIndexById(t.transactionId) != -1)
            {
                cout << "That transaction ID already exists.\n";
                continue;
            }

            cout << "Enter customer phone number: ";
            cin >> t.phoneNumber;

            cout << "Enter type (Deposit/Withdrawal/Transfer/Airtime): ";
            cin >> t.type;

            if (!validType(t.type))
            {
                cout << "Invalid transaction type.\n";
                continue;
            }

            cout << "Enter amount in UGX: ";
            if (!(cin >> t.amount) || t.amount <= 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid amount.\n";
                continue;
            }

            cout << "Enter date and time (YYYY-MM-DD_HH:MM): ";
            cin >> t.dateTime;

            t.status = "Successful";

            transactions.append(t);

            cout << "Transaction added successfully.\n";
        }

        else if (choice == 3)
        {
            int id;

            cout << "Enter transaction ID to remove: ";
            cin >> id;

            int index = transactions.findIndexById(id);

            if (index == -1)
            {
                cout << "Transaction not found.\n";
            }
            else
            {
                transactions.removeAt(index);
                cout << "Transaction removed successfully.\n";
            }
        }

        else if (choice == 4)
        {
            int id;

            cout << "Enter transaction ID to update: ";
            cin >> id;

            int index = transactions.findIndexById(id);

            if (index == -1)
            {
                cout << "Transaction not found.\n";
            }
            else
            {
                Transaction t = transactions.getAt(index);

                cout << "Enter new status (Successful/Failed/Pending): ";
                cin >> t.status;

                if (!validStatus(t.status))
                {
                    cout << "Invalid status.\n";
                }
                else
                {
                    transactions.updateAt(index, t);
                    cout << "Transaction updated successfully.\n";
                }
            }
        }

        else if (choice == 5)
        {
            int n = transactions.size();
            Transaction *records = transactions.toArray();

            auto byAmount = [](const Transaction &a,
                               const Transaction &b)
            {
                return a.amount < b.amount;
            };

            mergeSort(records, n, byAmount);

            cout << "\nTransactions sorted by amount:\n";

            for (int i = 0; i < n; i++)
            {
                displayTransaction(records[i]);
            }

            delete[] records;
        }

        else if (choice == 6)
        {
            int n = transactions.size();
            Transaction *records = transactions.toArray();

            auto byId = [](const Transaction &a,
                           const Transaction &b)
            {
                return a.transactionId < b.transactionId;
            };

            insertionSort(records, n, byId);

            cout << "\nTransactions sorted by ID:\n";

            for (int i = 0; i < n; i++)
            {
                displayTransaction(records[i]);
            }

            delete[] records;
        }

        else if (choice == 7)
        {
            int id;

            cout << "Enter transaction ID to search: ";
            cin >> id;

            int n = transactions.size();
            Transaction *records = transactions.toArray();

            auto byId = [](const Transaction &a,
                           const Transaction &b)
            {
                return a.transactionId < b.transactionId;
            };

            // Binary search requires sorted records.
            mergeSort(records, n, byId);

            auto compareId = [](const Transaction &t, int key)
            {
                if (t.transactionId < key)
                    return -1;
                if (t.transactionId > key)
                    return 1;
                return 0;
            };

            int result = binarySearch(records, n, id, compareId);

            if (result == -1)
            {
                cout << "Transaction not found.\n";
            }
            else
            {
                cout << "Transaction found:\n";
                displayTransaction(records[result]);
            }

            delete[] records;
        }

        else if (choice == 8)
        {
            if (saveTransactions(transactions, filename))
            {
                cout << "Transactions saved successfully.\n";
            }
            else
            {
                cout << "Could not save transactions.\n";
            }
        }

        else if (choice == 0)
        {
            if (saveTransactions(transactions, filename))
            {
                cout << "Transactions saved. Goodbye!\n";
            }
            else
            {
                cout << "Warning: could not save transactions.\n";
            }
        }

        else
        {
            cout << "Invalid menu option.\n";
        }

    } while (choice != 0);

    return 0;
}