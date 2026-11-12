#include <iostream>
#include <string>

#include "Transaction.h"
#include "SinglyLinkedList.h"
#include "Sorting.h"
#include "Searching.h"

using namespace std;

int passed = 0;
int failed = 0;

void check(const string &name, bool condition)
{
    if (condition)
    {
        cout << "[PASS] " << name << '\n';
        passed++;
    }
    else
    {
        cout << "[FAIL] " << name << '\n';
        failed++;
    }
}

Transaction makeTransaction(int id, double amount)
{
    Transaction t;
    t.transactionId = id;
    t.phoneNumber = "0771234567";
    t.type = "Deposit";
    t.amount = amount;
    t.dateTime = "2026-11-01_09:15";
    t.status = "Successful";
    return t;
}

int main()
{
    SinglyLinkedList<Transaction> list;

    check("New list is empty", list.isEmpty());

    check("Removal from empty list is rejected",
          !list.removeAt(0));

    list.append(makeTransaction(2001, 50000));

    check("One transaction can be added",
          list.size() == 1);

    list.append(makeTransaction(2002, 20000));
    list.append(makeTransaction(2003, 75000));

    check("Multiple transactions can be added",
          list.size() == 3);

    check("Existing ID can be found",
          list.findIndexById(2002) == 1);

    check("Missing ID returns -1",
          list.findIndexById(9999) == -1);

    check("First node can be removed",
          list.removeAt(0) && list.size() == 2);

    check("Last node can be removed",
          list.removeAt(list.size() - 1) && list.size() == 1);

    Transaction updated = makeTransaction(2002, 40000);

    check("Transaction can be updated",
          list.updateAt(0, updated) &&
              list.getAt(0).amount == 40000);

    SinglyLinkedList<Transaction> copied(list);

    list.removeAt(0);

    check("Deep copy remains independent",
          copied.size() == 1 && list.size() == 0);

    // Insertion sort with duplicate amounts
    Transaction arr[4] = {
        makeTransaction(1, 500),
        makeTransaction(2, 200),
        makeTransaction(3, 500),
        makeTransaction(4, 100)};

    auto byAmount = [](const Transaction &a,
                       const Transaction &b)
    {
        return a.amount < b.amount;
    };

    insertionSort(arr, 4, byAmount);

    check("Insertion sort orders records",
          arr[0].amount == 100 &&
              arr[1].amount == 200 &&
              arr[2].amount == 500 &&
              arr[3].amount == 500);

    check("Insertion sort preserves duplicate order",
          arr[2].transactionId == 1 &&
              arr[3].transactionId == 3);

    // Already sorted input
    Transaction sorted[3] = {
        makeTransaction(1, 100),
        makeTransaction(2, 200),
        makeTransaction(3, 300)};

    mergeSort(sorted, 3, byAmount);

    check("Merge sort handles already sorted data",
          sorted[0].amount == 100 &&
              sorted[2].amount == 300);

    // Reversed input
    Transaction reversed[3] = {
        makeTransaction(1, 300),
        makeTransaction(2, 200),
        makeTransaction(3, 100)};

    mergeSort(reversed, 3, byAmount);

    check("Merge sort handles reversed data",
          reversed[0].amount == 100 &&
              reversed[2].amount == 300);

    // Binary search
    Transaction searchRecords[3] = {
        makeTransaction(2001, 100),
        makeTransaction(2002, 200),
        makeTransaction(2003, 300)};

    auto compareId = [](const Transaction &t, int key)
    {
        if (t.transactionId < key)
            return -1;
        if (t.transactionId > key)
            return 1;
        return 0;
    };

    check("Binary search finds existing ID",
          binarySearch(searchRecords, 3, 2002, compareId) == 1);

    check("Binary search rejects absent ID",
          binarySearch(searchRecords, 3, 9999, compareId) == -1);

    check("Binary search handles empty input",
          binarySearch(searchRecords, 0, 2001, compareId) == -1);

    Transaction single[1] = {
        makeTransaction(2001, 500)};

    mergeSort(single, 1, byAmount);

    check("Merge sort handles one record",
          single[0].amount == 500);

    cout << "\n========== TEST SUMMARY ==========\n";
    cout << "Tests passed: " << passed << '\n';
    cout << "Tests failed: " << failed << '\n';

    return failed == 0 ? 0 : 1;
}