#include "pch.h"
#include "CppUnitTest.h"
#include "../CodeHomework1/CodeHomework1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:
        // проверка, что createArray корректно создаёт массив указанного размера
        TEST_METHOD(TestCreateArraySize)
        {
            int size = 5;
            std::vector<int> arr = createArray(size);
            Assert::AreEqual(size, static_cast<int>(arr.size()), L"Array size should match input size");
        }

        // проверка, что createArray создаёт массив с правильными значениями
        TEST_METHOD(TestCreateArrayValues)
        {
            std::vector<int> arr = createArray(5);
            for (int i = 0; i < 5; i++)
            {
                Assert::AreEqual(i, arr[i], L"Array values should be sequential from 0");
            }
        }

        // проверка работы removeElements (массив должен быть пустым после удаления)
        TEST_METHOD(TestRemoveElements)
        {
            std::vector<int> arr = createArray(10);
            removeElements(arr);
            Assert::IsTrue(arr.empty(), L"Array should be empty after removeElements");
        }

        // проверка работы removeElements на пустом массиве (не должно быть ошибки)
        TEST_METHOD(TestRemoveEmptyArray)
        {
            std::vector<int> arr;
            removeElements(arr);
            Assert::IsTrue(arr.empty(), L"Removing from an empty array should not cause issues");
        }

        // тест на создание и очистку массива из 1 млн. элементов
        TEST_METHOD(TestOneMillion)
        {
            int size = 1000000;
            std::vector<int> arr = createArray(size);
            Assert::AreEqual(size, static_cast<int>(arr.size()), L"Array size should match input size for 1 million");

            removeElements(arr);
            Assert::IsTrue(arr.empty(), L"Array should be empty after removeElements for 1 million elements");
        }

        // тест на создание и очистку массива из 10 млн. элементов
        TEST_METHOD(TestTenMillion)
        {
            int size = 10000000;
            std::vector<int> arr = createArray(size);
            Assert::AreEqual(size, static_cast<int>(arr.size()), L"Array size should match input size for 10 million");

            removeElements(arr);
            Assert::IsTrue(arr.empty(), L"Array should be empty after removeElements for 10 million elements");
        }
    };
}
