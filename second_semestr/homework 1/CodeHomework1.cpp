#include <iostream>
#include <vector>
#include <chrono>

// замеряем времечко
long long measureTime(void (*func)(std::vector<int>&), std::vector<int>& vec) {
    auto start = std::chrono::high_resolution_clock::now();
    func(vec);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

// запрашиваем инпут пользователя
long long getUserInput() {
    long long value;
    std::cout << "Enter the size of the array: ";
    while (!(std::cin >> value) || value <= 0) {
        std::cout << "Invalid input! Please enter a positive number: ";
        std::cin.clear();
        while (std::cin.get() != '\n');
    }
    return value;
}

// делаем сам массив
std::vector<int> createArray(int size) {
    std::vector<int> vec;
    for (int i = 0; i < size; i++) {
        vec.push_back(i);
    }
    return vec;
}

// убираем элементы массива
void removeElements(std::vector<int>& vec) {
    while (!vec.empty()) {
        vec.pop_back();
    }
}

int main() {
    int size = getUserInput();
    std::vector<int> numbers = createArray(size);
    long long timeTaken = measureTime(removeElements, numbers);
    std::cout << "Time taken to remove elements: " << timeTaken << " ms" << std::endl;
    system("pause");
    return 0;
}
