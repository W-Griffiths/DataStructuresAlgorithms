#include "CppUnitTest.h"
#include "Random.h"
#include "Utilities.h"
#include "MyMath.h"
#include "Array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utility {

	TEST_CLASS(Random)
	{
	public:

		TEST_METHOD(ProducesDifferentValuesWithoutSeed)
		{
			util::Random nonDeterministic1(0, 10);
			util::Random nonDeterministic2(0, 10);

			bool allTheSame = true;
			for (size_t i = 0; i < 100'000; i++)
			{
				if (nonDeterministic1.Next() != nonDeterministic2.Next()) {
					allTheSame = false;
					break;
				}
			}
			Assert::IsFalse(allTheSame);
		}

		TEST_METHOD(ProducesSameValuesWithSameSeed)
		{
			const int seed = 33;
			util::Random deterministic1(0, 10, seed);
			util::Random deterministic2(0, 10, seed);

			bool allTheSame = true;
			for (size_t i = 0; i < 1'000; i++)
			{
				if (deterministic1.Next() != deterministic2.Next()) {
					allTheSame = false;
					break;
				}
			}
			Assert::IsTrue(allTheSame);
		}

	};

	TEST_CLASS(SwapElements)
	{
	public:

		TEST_METHOD(SwappingChars)
		{
			ds::Array<char> array(3);

			array[0] = 'A';
			array[1] = 'B';
			array[2] = 'C';

			Assert::AreEqual('A', array[0]);
			Assert::AreEqual('B', array[1]);
			Assert::AreEqual('C', array[2]);

			Swap(array[0], array[2]);

			Assert::AreEqual('C', array[0]);
			Assert::AreEqual('B', array[1]);
			Assert::AreEqual('A', array[2]);

			Swap(array[2], array[1]);

			Assert::AreEqual('C', array[0]);
			Assert::AreEqual('A', array[1]);
			Assert::AreEqual('B', array[2]);
		}

	};

	TEST_CLASS(EvenAndOdd)
	{
	public:
		TEST_METHOD(LargeUIntValuesPass)
		{
			unsigned int bigUInt = 4'000'000'000;

			Assert::IsTrue(IsEven(bigUInt));
			Assert::IsFalse(IsOdd(bigUInt));

			Assert::IsTrue(IsOdd(bigUInt + 1));
			Assert::IsFalse(IsEven(bigUInt + 1));
		}
	};
}
