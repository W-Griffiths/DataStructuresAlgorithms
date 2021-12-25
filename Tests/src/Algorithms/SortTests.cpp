#include "CppUnitTest.h"
#include "Sort.h"
#include "Array.h"
#include "List.h"
#include "Random.h"
#include "Utilities.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Sort {

	TEST_CLASS(Utility)
	{
	public:

		TEST_METHOD(Random)
		{
			util::Random* nonDeterministic1 = new util::Random(0, 10);
			util::Random* nonDeterministic2 = new util::Random(0, 10);

			bool allTheSame = true;
			for (size_t i = 0; i < 100'000; i++)
			{
				if (nonDeterministic1->Next() != nonDeterministic2->Next()) {
					allTheSame = false;
					break;
				}
			}
			Assert::IsFalse(allTheSame);
			delete nonDeterministic1;
			delete nonDeterministic2;

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
		
		TEST_METHOD(ShuffleInts)
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
			
			util::Shuffle(arrayA);
			util::Shuffle(arrayB);
			util::Shuffle(arrayC);

			Assert::IsTrue(arrayA != arrayB || arrayA != arrayC);
		}

		TEST_METHOD(ShuffleStrings)
		{
			ds::List<std::string> strings;
			strings.Add("The");
			strings.Add("quick");
			strings.Add("brown");
			strings.Add("fox");
			strings.Add("jumps");
			strings.Add("over");
			strings.Add("the");
			strings.Add("lazy");
			strings.Add("dog");


			ds::List<std::string> stringsCopy = strings;

			for (size_t i = 0; i < strings.Size(); i++) {
				Assert::IsTrue(strings[i] == stringsCopy[i]);
			}


			util::Shuffle(strings.begin(), strings.end());

			bool theSame = true;
			for (size_t i = 0; i < strings.Size(); i++) {
				if (strings[i] != stringsCopy[i]) {
					theSame = false;
					break;
				}
			}

			Assert::IsFalse(theSame);
		}

	};

}
