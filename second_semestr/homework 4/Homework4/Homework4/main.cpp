#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex mtx;

void generateArray(std::vector<int>& arr, size_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 1000000);
    arr.resize(size);
    for (size_t i = 0; i < size; ++i)
        arr[i] = dist(gen);
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quicksort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

void threaded_quicksort(std::vector<int>& arr, int low, int high, int max_depth, int depth = 0) {
    if (low < high) {
        int pi = partition(arr, low, high);

        if (depth < max_depth) {
            std::thread left([&arr, low, pi, max_depth, depth]() {
                threaded_quicksort(arr, low, pi - 1, max_depth, depth + 1);
            });

            threaded_quicksort(arr, pi + 1, high, max_depth, depth + 1);
            left.join();
        } else {
            quicksort(arr, low, pi - 1);
            quicksort(arr, pi + 1, high);
        }
    }
}

long long measure_execution_time(std::function<void()> func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main() {
    const size_t array_size = 10000;

    std::vector<int> data;

    generateArray(data, array_size);
    long long time_seq = measure_execution_time([&]() {
        quicksort(data, 0, static_cast<int>(data.size() - 1));
    });
    std::cout << "Sequential QuickSort: " << time_seq << " ms" << std::endl;

    generateArray(data, array_size);
    long long time_2 = measure_execution_time([&]() {
        threaded_quicksort(data, 0, static_cast<int>(data.size() - 1), 1);
    });
    std::cout << "Threaded QuickSort (2 threads): " << time_2 << " ms" << std::endl;

    generateArray(data, array_size);
    long long time_4 = measure_execution_time([&]() {
        threaded_quicksort(data, 0, static_cast<int>(data.size() - 1), 2);
    });
    std::cout << "Threaded QuickSort (4 threads): " << time_4 << " ms" << std::endl;

    generateArray(data, array_size);
    long long time_8 = measure_execution_time([&]() {
        threaded_quicksort(data, 0, static_cast<int>(data.size() - 1), 3);
    });
    std::cout << "Threaded QuickSort (8 threads): " << time_8 << " ms" << std::endl;

    return 0;
}
