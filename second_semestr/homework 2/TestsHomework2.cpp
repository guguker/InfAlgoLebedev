#include "pch.h"
#include "CppUnitTest.h"
#include "..//CodeHomework2/CodeHomework2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const double expected_area = 4.0;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(Equal_N_2)
		{
			double result = simpson_rule(integrand, 4, 8, 2);
			Assert::AreEqual(expected_area, result, 0.001, L"Area should be equal with tolerance 0.001 for N=2");
		}

		TEST_METHOD(Equal_N_10)
		{
			double result = simpson_rule(integrand, 4, 8, 10);
			Assert::AreEqual(expected_area, result, 0.001, L"Area should be equal with tolerance 0.001 for N=10");
		}

		TEST_METHOD(Equal_N_100)
		{
			double result = simpson_rule(integrand, 4, 8, 100);
			Assert::AreEqual(expected_area, result, 0.001, L"Area should be equal with tolerance 0.001 for N=100");
		}

		TEST_METHOD(Equal_N_10000)
		{
			double result = simpson_rule(integrand, 4, 8, 10000);
			Assert::AreEqual(expected_area, result, 0.001, L"Area should be equal with tolerance 0.001 for N=10000");
		}

		TEST_METHOD(Equal_N_100000)
		{
			double result = simpson_rule(integrand, 4, 8, 100000);
			Assert::AreEqual(expected_area, result, 0.001, L"Area should be equal with tolerance 0.001 for N=100000");
		}

		TEST_METHOD(Equal_N_1000000)
		{
			double result = simpson_rule(integrand, 4, 8, 1000000);
			Assert::AreEqual(expected_area, result, 0.001, L"Area should be equal with tolerance 0.001 for N=1000000");
		}
	};
}

