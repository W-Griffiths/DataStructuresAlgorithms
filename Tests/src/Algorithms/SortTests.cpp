#include "CppUnitTest.h"
#include "Sort.h"
#include "Array.h"
#include "Random.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Sort {

	TEST_CLASS(Utility)
	{
	public:

		TEST_METHOD(Random)
		{
			util::Random nonDeterministic1(0, 10);
			util::Random nonDeterministic2(0, 10);

			bool allTheSame = true;
			for (size_t i = 0; i < 1'000'000; i++)
			{
				if (nonDeterministic1.Next() != nonDeterministic2.Next()) {
					allTheSame = false;
					break;
				}
			}
			Assert::IsFalse(allTheSame);

			const int seed = 33;
			util::Random deterministic1(0, 10, seed);
			util::Random deterministic2(0, 10, seed);

			allTheSame = true;
			for (size_t i = 0; i < 1'000; i++)
			{
				if (deterministic1.Next() != deterministic2.Next()) {
					allTheSame = false;
					break;
				}
			}
			Assert::IsTrue(allTheSame);
		}
		
		TEST_METHOD(Shuffle)
		{
			const int length = 1000;
			ds::Array<int> arrayA(length);
			ds::Array<int> arrayB(length);
			ds::Array<int> arrayC(length);

			for (int i = 0; i < length; i++)
			{
				arrayA[i] = i;
				arrayB[i] = i;
				arrayC[i] = i;
			}

			Assert::IsTrue(arrayA == arrayB || arrayA == arrayC);
			
			alg::Shuffle(arrayA);
			alg::Shuffle(arrayB);
			alg::Shuffle(arrayC);

			Assert::IsTrue(arrayA != arrayB || arrayA != arrayC);
		}

		TEST_METHOD(ShuffleStrings)
		{
			const int length = 20;
			ds::Array<int> arrayA(length);
			ds::Array<int> arrayB(length);
			ds::Array<int> arrayC(length);

			for (int i = 0; i < length; i++)
			{
				arrayA[i] = i;
				arrayB[i] = i;
				arrayC[i] = i;
			}

			Assert::IsTrue(arrayA == arrayB || arrayA == arrayC);

			alg::Shuffle(arrayA);
			alg::Shuffle(arrayB);
			alg::Shuffle(arrayC);

			Assert::IsTrue(arrayA != arrayB || arrayA != arrayC);
		}

	};

}
