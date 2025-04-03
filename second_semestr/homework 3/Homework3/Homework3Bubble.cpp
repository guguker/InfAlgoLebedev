#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

// так называемый пузырёк сортировка
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
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

    bubbleSort(arr);

    cout << "Sorted array:\n";
    printArray(arr);

    return 0;
}

