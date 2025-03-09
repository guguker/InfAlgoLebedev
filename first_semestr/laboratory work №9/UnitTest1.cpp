#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\user\source\repos\practice four\practice four.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        float x = 2;
        float y = 1;

        float S = log(x) * tan(y);
        float R = sqrt(pow(x, 2) + pow(y, 2)) / pow(2, log2(x));

        TEST_METHOD(isSequalzero)
        {
            Assert::AreEqual(S, 0.0f);
        }

        TEST_METHOD(isRequalzero)
        {
            Assert::AreEqual(R, 0.0f);
        }

        TEST_METHOD(isSmoreThanR)
        {
            Assert::IsTrue(S > R);
        }

        TEST_METHOD(isRmoreThanS)
        {
            Assert::IsTrue(R > S);
        }

        TEST_METHOD(isSgreaterThanZero)
        {
            Assert::IsTrue(S > 0);
        }

        TEST_METHOD(isRgreaterThanZero)
        {
            Assert::IsTrue(R > 0);
        }
    };
}
