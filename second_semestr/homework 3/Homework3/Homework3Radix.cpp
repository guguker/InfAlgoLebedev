#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

// ���������� ������� :)
vector<int> combineBuckets(const vector<vector<int>>& buckets) {
    vector<int> combinedArray;
    for (const auto& bucket : buckets) {
        combinedArray.insert(combinedArray.end(), bucket.begin(), bucket.end());
    }
    return combinedArray;
}

// ��������� �� �������
void sortByDigit(vector<int>& arr, int digitPlace) {

    // ������ ������� ��� ��������
    vector<vector<int>> buckets(10);

    // ������������ �� �������� ��� ������ :)
    // ���� �� ������� �������-�������� ����, �� ������� � �������� ������
    for (int num : arr) {
        int bucketIndex = (num / digitPlace) % 10;
        buckets[bucketIndex].push_back(num);
    }

    // �� ������ ����� � �������
    arr = combineBuckets(buckets);
}

// ��� ���������� ������� ����������
void radixSort(vector<int>& arr) {

    // ������������ �����?
    int maxVal = *max_element(arr.begin(), arr.end());

    // �������� � ������ � ������ ��� �� ��������, ������ � ��
    int digitPlace = 1;
    while (maxVal / digitPlace > 0) {
        sortByDigit(arr, digitPlace);
        digitPlace *= 10;  // ������� � ���������� �������
    }
}

// ������� ������
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

    // ������ �� 20 ����� �� 1 �� 100
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


