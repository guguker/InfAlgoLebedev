#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// так называемый квиксорт который делит на больше/меньше/равно
void quickSort3Way(vector<int>& arr, int low, int high) {
    if (low >= high) return;

    // выбираем случайный pivot
    int randomIndex = low + rand() % (high - low + 1);
    int pivot = arr[randomIndex];
    swap(arr[randomIndex], arr[low]);

    // начинаем разделение
    int lt = low;
    int gt = high;
    int i = low + 1;

    while (i <= gt) {
        if (arr[i] < pivot) {
            swap(arr[i], arr[lt]);
            i++;
            lt++;
        }
        else if (arr[i] > pivot) {
            swap(arr[i], arr[gt]);
            gt--;
        }
        else {
            i++;
        }
    }

    // рекурсивно сортируем < pivot и > pivot части
    quickSort3Way(arr, low, lt - 1);
    quickSort3Way(arr, gt + 1, high);
}

// выводим массив
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));

    int N = 1000000000; // количество случайных чисел
    int RANGE = N; // диапазон значений

    vector<int> arr;
    arr.reserve(N); // резервируем память заранее

    // массив из N случайных чисел от 1 до RANGE
    for (int i = 0; i < N; ++i) {
        arr.push_back(rand() % RANGE + 1);
    }

    cout << "Original array (first 20 elements):\n";
    for (int i = 0; i < 20 && i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    // начинаем замер времени
    auto start = high_resolution_clock::now();

    quickSort3Way(arr, 0, arr.size() - 1);

    // заканчиваем замер времени
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Sorted array (first 20 elements):\n";
    for (int i = 0; i < 20 && i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    cout << "Time taken by quickSort3Way: " << duration.count() << " milliseconds" << endl;

    return 0;
}