#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono> // добавили chrono для замеров времени

using namespace std;
using namespace std::chrono;

// так называемый пузырёк сортировка
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false; // оптимизация: если ничего не поменялось — массив уже отсортирован
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// выводим массив
void printFirstElements(const vector<int>& arr, int count = 20) {
    for (int i = 0; i < count && i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

int main() {
    srand(time(0));

    int N = 1000000;              // количество случайных чисел (НЕ ставь больше ~10,000 — будет долго)
    int RANGE = 100;       // диапазон значений

    vector<int> arr;
    arr.reserve(N);            // резервируем память заранее

    // массив из N случайных чисел от 1 до RANGE
    for (int i = 0; i < N; ++i) {
        arr.push_back(rand() % RANGE + 1);
    }

    cout << "Original array (first 20 elements):\n";
    printFirstElements(arr);

    // начинаем замер времени
    auto start = high_resolution_clock::now();

    bubbleSort(arr);

    // заканчиваем замер времени
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Sorted array (first 20 elements):\n";
    printFirstElements(arr);

    cout << "Time taken by bubbleSort: " << duration.count() << " milliseconds" << endl;

    return 0;
}