/* Practice with Radix Sort
 * Written by Kevin Morris */
#include <iostream>
#include <list>
using namespace std;

// Base 10 (decimal) for Radix sort
const int BASE = 10;

int max(int values[], int sz)
{
    int highest = values[0];
    for(int i = 1; i < sz; ++i)
    {
        if(values[i] > highest)
            highest = values[i];
    }

    return highest;
}

void radixSort(int values[], int sz, int max)
{
    list<int> bucket[BASE];
    list<int>::iterator iter;

    for(int n = 1; n < max; n *= BASE)
    {
        for(int i = 0; i < sz; ++i)
            bucket[(values[i]/n) % BASE].push_back(values[i]);

        for(int k = 0, i = 0; i < BASE; bucket[i++].clear())
        {
            for(iter = bucket[i].begin(); iter != bucket[i].end(); ++iter)
                values[k++] = *iter;
        }

    }

}

int main(int argc, char *argv[])
{
    const int HAND_SIZE = 5;

    int nums[HAND_SIZE] = {8, 6, 5, 9, 7};
    int maxValue = max(nums, HAND_SIZE);

    radixSort(nums, HAND_SIZE, maxValue);

    for(int i = 0; i < HAND_SIZE; ++i)
        cout << nums[i] << endl;

    return 0;
}

