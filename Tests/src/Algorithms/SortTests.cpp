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

			util::Shuffle(arrayB);
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

}
