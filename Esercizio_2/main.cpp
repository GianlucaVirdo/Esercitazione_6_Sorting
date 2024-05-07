#define NUMTESTS 400
#include <iostream>
#include <vector>
#include <chrono>
#include <sstream>
#include <random>
#include "SortingAlgorithm.hpp"

using namespace std;
using namespace SortLibrary;
using namespace chrono;

vector<int> generateVector(int size, string type)
{
    vector<int> vec(size);

    if (type == "random")
    {
        for (int i = 0; i < size; i++)
            vec.push_back(rand());
    }
    else if (type == "completely_unsorted")
    {
        for (int i = size; i > 0; i--)
            vec.push_back(i);
    }
    return vec;
}

double testSortingAlgorithm(void (*sortFunc)(vector<int>&), vector<int>& vec)
{
    auto start = steady_clock::now();
    sortFunc(vec);
    auto end = steady_clock::now();
    duration<double> elapsed_seconds = end - start;
    return elapsed_seconds.count();
}

double calculateAverageTime(const vector<double>& times)
{
    double total = 0.0;
    for (double time : times)
        total += time;
    return total / times.size();
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cerr << "Insert an integer number as a command line argument" << endl;
        return 1;
    }

    srand(time(nullptr));

    int vectorSize;
    istringstream(argv[1]) >> vectorSize;

    vector<double> bubbleSortTimesRandom;
    vector<double> mergeSortTimesRandom;

    for (int i = 0; i < NUMTESTS; i++)
    {
        vector<int> intVectorRandom = generateVector(vectorSize, "random");

        bubbleSortTimesRandom.push_back(testSortingAlgorithm(BubbleSort<int>, intVectorRandom));

        mergeSortTimesRandom.push_back(testSortingAlgorithm(MergeSort<int>, intVectorRandom));
    }

    cout << "BubbleSort Average Time (Random):" << calculateAverageTime(bubbleSortTimesRandom) << "s" << endl;
    cout << endl;
    cout << "MergeSort Average Time (Random):" << calculateAverageTime(mergeSortTimesRandom) << "s" << endl;
    cout << endl;

    vector<double> bubbleSortTimesCompletelyUnsorted;
    vector<double> mergeSortTimesCompletelyUnsorted;

    for (int i = 0; i < NUMTESTS; i++)
    {
        vector<int> intVectorCompletelyUnsorted = generateVector(vectorSize + i, "completely_unsorted");

        bubbleSortTimesCompletelyUnsorted.push_back(testSortingAlgorithm(BubbleSort<int>, intVectorCompletelyUnsorted));

        mergeSortTimesCompletelyUnsorted.push_back(testSortingAlgorithm(MergeSort<int>, intVectorCompletelyUnsorted));
    }

    cout << "BubbleSort Average Time (Completely Unsorted):" << calculateAverageTime(bubbleSortTimesCompletelyUnsorted) << "s" << endl;
    cout << endl;
    cout << "MergeSort Average Time (Completely Unsorted):" << calculateAverageTime(mergeSortTimesCompletelyUnsorted) << "s" << endl;

    return 0;
}
