#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono> // добавили chrono дл€ замеров времени

using namespace std;
using namespace std::chrono;

// объедин€ем корзины пр€м как  –ќЋ» :)
// если увидели это - напишите об этом в ответном письме :)
vector<int> combineBuckets(const vector<vector<int>>& buckets) {
    vector<int> combinedArray;
    for (const auto& bucket : buckets) {
        combinedArray.insert(combinedArray.end(), bucket.begin(), bucket.end());
    }
    return combinedArray;
}

// сортируем по разр€ду
void sortByDigit(vector<int>& arr, int digitPlace) {
    vector<vector<int>> buckets(10);
    for (int num : arr) {
        int bucketIndex = (num / digitPlace) % 10;
        buckets[bucketIndex].push_back(num);
    }
    arr = combineBuckets(buckets);
}

// так называема€ рэйдикс сортировка
void radixSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    int digitPlace = 1;
    while (maxVal / digitPlace > 0) {
        sortByDigit(arr, digitPlace);
        digitPlace *= 10;
    }
}

// выводим первые 20 элементов массива дл€ нј√ляднќ—ти
void printFirstElements(const vector<int>& arr) {
    for (int i = 0; i < 20 && i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));

    int N = 1000000000;        // <- количество элементов массива
    int RANGE = 100; // <- диапазон значений

    vector<int> arr;
    arr.reserve(N); // резервируем пам€ть заранее

    // массив из N случайных чисел от 1 до RANGE
    for (int i = 0; i < N; ++i) {
        arr.push_back(rand() % RANGE + 1);
    }

    cout << "Original array (first 20 elements):\n";
    printFirstElements(arr);

    auto start = high_resolution_clock::now();

    radixSort(arr);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Sorted array (first 20 elements):\n";
    printFirstElements(arr);

    cout << "Time taken by radixSort: " << duration.count() << " milliseconds" << endl;

    return 0;
}