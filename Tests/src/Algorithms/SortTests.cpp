#include "CppUnitTest.h"
#include "Sort.h"
#include "Utilities.h"
#include "Array.h"
#include "List.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Sort {

	TEST_CLASS(Quicksort)
	{
	public:

		TEST_METHOD(SortNumbers)
		{
			const int length = 1000;
			ds::Array<int> arrayA(length);
			ds::Array<int> arrayB(length);

			for (int i = 0; i < length; i++)
			{
				arrayA[i] = i;
				arrayB[i] = i;
			}

			Assert::IsTrue(arrayA == arrayB);

			alg::Shuffle(arrayB);
			Assert::IsTrue(arrayA != arrayB);

			alg::Quicksort(arrayB);

			Assert::IsTrue(arrayA == arrayB);
		}

		TEST_METHOD(SortStrings)
		{
			ds::List<std::string> words;
			words.Add("Beta");
			words.Add("Foxtrot");
			words.Add("Alpha");
			words.Add("Charlie");
			words.Add("Echo");
			words.Add("Delta");

			alg::Quicksort(words.begin(), words.end());

			Assert::AreEqual(std::string("Alpha"), words[0]);
			Assert::AreEqual(std::string("Beta"), words[1]);
			Assert::AreEqual(std::string("Charlie"), words[2]);
			Assert::AreEqual(std::string("Delta"), words[3]);
			Assert::AreEqual(std::string("Echo"), words[4]);
			Assert::AreEqual(std::string("Foxtrot"), words[5]);
		}

		TEST_METHOD(SortChars)
		{
			const int length = 26;
			ds::Array<char> keyboard("qwertyuiopasdfghjklzxcvbnm", length);
			ds::Array<char> alphabet("abcdefghijklmnopqrstuvwxyz", length);

			Assert::IsTrue(keyboard != alphabet);

			alg::Quicksort(keyboard);

			Assert::IsTrue(keyboard == alphabet);
		}

	};

	TEST_CLASS(Shuffle)
	{
	public:

		TEST_METHOD(ShuffleInts)
		{
			const int length = 1000;
			ds::Array<int> arrayA(length);
			ds::Array<int> arrayB(length);
			ds::Array<int> arrayC(length);

			for (int i = 0; i < length; i++) {
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


			alg::Shuffle(strings.begin(), strings.end());

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
