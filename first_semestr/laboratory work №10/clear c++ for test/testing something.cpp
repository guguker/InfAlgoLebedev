#include <iostream>
#include <vector>
#include <ctime>

void calculateEvenNTimes(int N) {
    std::clock_t start_time = std::clock();

    for (int i = 0; i < N; ++i) {
        auto countEvenNumbers = [](const std::vector<int>& array) {
            int count = 0;
            for (int num : array) {
                if (num % 2 == 0) {
                    ++count;
                }
            }
            return count;
            };

        std::vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        int even_count = countEvenNumbers(array);

        // std::cout << "The number of even numbers in the array: " << even_count << std::endl;
    }

    std::clock_t end_time = std::clock();
    double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;

    std::cout << "Time taken: " << time_taken << " seconds" << std::endl;
}

int main() {
    calculateEvenNTimes(10000);
    return 0;
}














