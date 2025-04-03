#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

// делим массив по опорному элементу
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;       

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// так называемый квик сорт
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
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

    quickSort(arr, 0, arr.size() - 1);

    cout << "Sorted array:\n";
    printArray(arr);

    return 0;
}

