#include <iostream>
#include <chrono>
#include <random>
#include <iomanip>

#include "Transaction.h"
#include "Sorting.h"

using namespace std;
using namespace chrono;

Transaction *generateRecords(int n, mt19937 &generator)
{
    Transaction *records = new Transaction[n];

    uniform_int_distribution<int> distribution(1000, 1000000);

    for (int i = 0; i < n; i++)
    {
        records[i].transactionId = i + 1;
        records[i].phoneNumber = "0771234567";
        records[i].type = "Deposit";
        records[i].amount = distribution(generator);
        records[i].dateTime = "2026-11-01_09:15";
        records[i].status = "Successful";
    }

    return records;
}

int main()
{
    int sizes[] = {
        1000, 2000, 4000, 8000,
        16000, 32000, 64000};

    mt19937 generator(42);

    double previousInsertion = 0;
    double previousMerge = 0;

    cout << fixed << setprecision(6);

    cout << "N,InsertionAverageMs,MergeAverageMs,"
         << "InsertionRatio,MergeRatio\n";

    for (int n : sizes)
    {
        double insertionTotal = 0;
        double mergeTotal = 0;

        for (int repeat = 0; repeat < 3; repeat++)
        {
            Transaction *original = generateRecords(n, generator);

            Transaction *insertionData = new Transaction[n];
            Transaction *mergeData = new Transaction[n];

            for (int i = 0; i < n; i++)
            {
                insertionData[i] = original[i];
                mergeData[i] = original[i];
            }

            auto byAmount = [](const Transaction &a,
                               const Transaction &b)
            {
                return a.amount < b.amount;
            };

            auto start1 = steady_clock::now();

            insertionSort(insertionData, n, byAmount);

            auto end1 = steady_clock::now();

            insertionTotal += duration<double, milli>(
                                  end1 - start1)
                                  .count();

            auto start2 = steady_clock::now();

            mergeSort(mergeData, n, byAmount);

            auto end2 = steady_clock::now();

            mergeTotal += duration<double, milli>(
                              end2 - start2)
                              .count();

            delete[] original;
            delete[] insertionData;
            delete[] mergeData;
        }

        double insertionAverage = insertionTotal / 3.0;
        double mergeAverage = mergeTotal / 3.0;

        double insertionRatio = previousInsertion == 0
                                    ? 0
                                    : insertionAverage / previousInsertion;

        double mergeRatio = previousMerge == 0
                                ? 0
                                : mergeAverage / previousMerge;

        cout << n << ","
             << insertionAverage << ","
             << mergeAverage << ","
             << insertionRatio << ","
             << mergeRatio << '\n';

        previousInsertion = insertionAverage;
        previousMerge = mergeAverage;
    }

    return 0;
}