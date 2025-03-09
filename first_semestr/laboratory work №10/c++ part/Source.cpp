#include "pch.h"
#include "Header.h"

int countEvenNumbers(const int* array, const int size) {
    if (array == nullptr || size <= 0) {
        return 0;
    }

    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (array[i] % 2 == 0) {
            ++count;
        }
    }
    return count;
}
