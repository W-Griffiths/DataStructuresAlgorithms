#include "CppUnitTest.h"
#include "Array.h"
#include "List.h"
#include "Random.h"
#include "Utilities.h"
#include <string>

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


	TEST_CLASS(Swap)
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

			util::Swap(array[0], array[2]);

			Assert::AreEqual('C', array[0]);
			Assert::AreEqual('B', array[1]);
			Assert::AreEqual('A', array[2]);

			util::Swap(array[2], array[1]);

			Assert::AreEqual('C', array[0]);
			Assert::AreEqual('A', array[1]);
			Assert::AreEqual('B', array[2]);
		}

	};

	TEST_CLASS(ShiftElements)
	{
	public:

		TEST_METHOD(ShiftingChars)
		{
			ds::Array<char> array("dogcat");

			util::ShiftElements(array.begin(), array.begin() + 3, 3);

			Assert::AreEqual(std::string{ "dogdog" }, util::ToString(array));

			ds::Array<char> array2("It's raining cats");

			util::ShiftElements(array2.begin() + 13, array2.end(), -8);

			Assert::AreEqual(std::string{ "It's catsing cats" }, util::ToString(array2));
		}

		TEST_METHOD(ShiftOverlap)
		{
			ds::Array<char> array("doggo");

			util::ShiftElements(array.begin(), array.begin() + 3, 2);

			Assert::AreEqual(std::string{ "dodog" }, util::ToString(array));

			ds::Array<char> array2("Kimi Raikonnen");

			util::ShiftElements(array2.begin() + 5, array2.end(), -4);

			Assert::AreEqual(std::string{ "KRaikonnennnen" }, util::ToString(array2));
		}

		TEST_METHOD(ShiftingBy0DoesNothing)
		{
			ds::Array<char> array("Du Bist Weltmeister!");

			util::ShiftElements(array.begin(), array.begin() + 5, 0);

			Assert::AreEqual(std::string{ "Du Bist Weltmeister!" }, util::ToString(array));
		}

		TEST_METHOD(ShiftingEmptySequenceDoesNothing)
		{
			ds::Array<char> array("Thirty years ago...");

			util::ShiftElements(array.begin() + 5, array.begin() + 5, 0);

			Assert::AreEqual(std::string{ "Thirty years ago..." }, util::ToString(array));
		}

	};

}
