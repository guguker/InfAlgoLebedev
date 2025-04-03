#include "pch.h"
#include "..//Homework3/Homework3Radix.cpp"  // Подключаем файл с реализацией сортировки
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Homework3Tests
{
    TEST_CLASS(Homework3TestRadix)
    {
    public:

        // вместо циклов в тест методах я сообразил такую функцию :)
        bool isSorted(const vector<int>& arr) {
            for (size_t i = 1; i < arr.size(); i++) {
                if (arr[i] < arr[i - 1]) {
                    return false;
                }
            }
            return true;
        }

        TEST_METHOD(TestRadixSort_1_usual)  // массив с нормальными числами
        {
            vector<int> arr = { 34, 23, 45, 67, 12, 89, 53, 17, 28, 92, 74, 56, 49, 77, 33, 8, 56, 15, 67, 99 };
            radixSort(arr);
            Assert::IsTrue(isSorted(arr), L"Array is not sorted! :(");
        }

        TEST_METHOD(TestRadixSort_2_negative)  // массив с фулл отрицательными числами
        {
            vector<int> arr = { -15, -34, -8, -45, -3, -23, -56, -12, -72, -89, -28, -92, -9, -64, -33, -77, -49, -41, -3, -18 };
            radixSort(arr);
            Assert::IsTrue(isSorted(arr), L"Array is not sorted! :(");
        }

        TEST_METHOD(TestRadixSort_3_zero)  // нулевой массивчик
        {
            vector<int> arr = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            radixSort(arr);
            Assert::IsTrue(isSorted(arr), L"Array is not sorted! :(");
        }

        TEST_METHOD(TestRadixSort_4_moreThan100)  // массив с числами > 100
        {
            vector<int> arr = { 120, 150, 110, 250, 130, 190, 200, 220, 170, 180, 300, 270, 140, 160, 230, 190, 1000, 300, 950, 400 };
            radixSort(arr);
            Assert::IsTrue(isSorted(arr), L"Array is not sorted! :(");
        }

        TEST_METHOD(TestRadixSort_5_unoriginal)  // совершенно неоригинальный массив
        {
            vector<int> arr = { 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
            radixSort(arr);
            Assert::IsTrue(isSorted(arr), L"Array is not sorted! :(");
        }
    };
}