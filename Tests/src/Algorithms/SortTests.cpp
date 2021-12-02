#include "CppUnitTest.h"
#include "Sort.h"
#include "Array.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Sort {

	TEST_CLASS(Utility)
	{
	public:

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
