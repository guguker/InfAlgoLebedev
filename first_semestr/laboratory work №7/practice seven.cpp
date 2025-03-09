#include <iostream>
#include <vector>
#include <set>

// Задание 1: Работа с массивами

// Функция для вычисления суммы элементов массива
void calculateSum(const int* arr, int size, int& sum) {
    sum = 0; // Инициализация суммы
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
}

// Функция для создания массива B из элементов массива A, квадрат которых меньше 1000
void filterArray(const int* arr, int size, std::vector<int>& result) {
    for (int i = 0; i < size; i++) {
        int square = arr[i] * arr[i];
        if (square < 1000) {
            result.push_back(arr[i]);
        }
    }
}

// Функция для нахождения объединения двух множеств
void unionSets(const std::set<int>& setA, const std::set<int>& setB, std::set<int>& result) {
    result = setA;
    result.insert(setB.begin(), setB.end());
}

int main() {
    // Задание 1: Работа с массивами
    const int sizeA = 10;
    int A[sizeA];
    std::vector<int> B;

    // Ввод элементов массива A
    std::cout << "Type 10 elements of array A" << std::endl;
    for (int i = 0; i < sizeA; i++) {
        std::cin >> A[i];
    }

    // Создание массива B
    filterArray(A, sizeA, B);

    // Вычисление суммы элементов массивов A и B
    int sumA = 0, sumB = 0;
    calculateSum(A, sizeA, sumA);
    calculateSum(B.data(), B.size(), sumB);

    // Вывод массива B и сумм
    std::cout << "Array B (elements of array A, whose square is less than 1000): ";
    for (int elem : B) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::cout << "Sum of Array A elements: " << sumA << std::endl;
    std::cout << "Sum of Array B elements: " << sumB << std::endl;

    ////////////////////////////////////////////////////////////////////////////////////////////

    // Задание 2: Работа с множествами

    std::set<int> A_set, B_set, unionAB;
    int nA, nB, elem;

    std::cout << "Type the number of elements of the set A: ";
    std::cin >> nA;
    std::cout << "Type the elements of the set A: " << std::endl;
    for (int i = 0; i < nA; i++) {
        std::cin >> elem;
        A_set.insert(elem);
    }

    std::cout << "Type the number of elements of the set B: ";
    std::cin >> nB;
    std::cout << "Type the elements of the set B: " << std::endl;
    for (int i = 0; i < nB; i++) {
        std::cin >> elem;
        B_set.insert(elem);
    }

    // Нахождение объединения множеств
    unionSets(A_set, B_set, unionAB);

    std::cout << "The union of sets contains " << unionAB.size() << " elements." << std::endl;
    std::cout << "United elements: ";
    for (int elem : unionAB) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
