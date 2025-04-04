#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

// объединяем корзины :)
vector<int> combineBuckets(const vector<vector<int>>& buckets) {
    vector<int> combinedArray;
    for (const auto& bucket : buckets) {
        combinedArray.insert(combinedArray.end(), bucket.begin(), bucket.end());
    }
    return combinedArray;
}

// сортируем по разряду
void sortByDigit(vector<int>& arr, int digitPlace) {

    // делаем корзины для разрядов
    vector<vector<int>> buckets(10);

    // раскладываем по корзинам как КРОЛИК :)
    // если вы увидели строчку-пасхалку выше, то скажите в ответном письме
    for (int num : arr) {
        int bucketIndex = (num / digitPlace) % 10;
        buckets[bucketIndex].push_back(num);
    }

    // из корзин кладём в массивы
    arr = combineBuckets(buckets);
}

// так называемая рэйдикс сортировка
void radixSort(vector<int>& arr) {

    // максимальное число?
    int maxVal = *max_element(arr.begin(), arr.end());

    // начинаем с единиц и дальше идём по десяткам, сотням и тд
    int digitPlace = 1;
    while (maxVal / digitPlace > 0) {
        sortByDigit(arr, digitPlace);
        digitPlace *= 10;  // переход к следующему разряду
    }
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

    set<int> uniqueNumbers;
    vector<int> arr;

    // массив из 20 чисел от 1 до 100
    while (uniqueNumbers.size() < 20) {
        int num = rand() % 100 + 1;
        if (uniqueNumbers.insert(num).second) {
            arr.push_back(num);
        }
    }

    cout << "Original array:\n";
    printArray(arr);

    radixSort(arr);

    cout << "Original array:\n";
    printArray(arr);

    return 0;
}

// blablabla


