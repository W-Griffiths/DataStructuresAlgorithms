#include "CppUnitTest.h"
#include "CollectionAlgorithms.h"
#include "Array.h"
#include "Utilities.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CollectionAlgorithms {

	TEST_CLASS(ShiftElements)
	{
	public:

		TEST_METHOD(ShiftingChars)
		{
			ds::Array<char> array("dogcat");

			alg::ShiftElements(array.begin(), array.begin() + 3, 3);

			Assert::AreEqual(std::string{ "dogdog" }, util::ToString(array));

			ds::Array<char> array2("It's raining cats");

			alg::ShiftElements(array2.begin() + 13, array2.end(), -8);

			Assert::AreEqual(std::string{ "It's catsing cats" }, util::ToString(array2));
		}

		TEST_METHOD(ShiftOverlap)
		{
			ds::Array<char> array("doggo");

			alg::ShiftElements(array.begin(), array.begin() + 3, 2);

			Assert::AreEqual(std::string{ "dodog" }, util::ToString(array));

			ds::Array<char> array2("Kimi Raikonnen");

			alg::ShiftElements(array2.begin() + 5, array2.end(), -4);

			Assert::AreEqual(std::string{ "KRaikonnennnen" }, util::ToString(array2));
		}

		TEST_METHOD(ShiftingBy0DoesNothing)
		{
			ds::Array<char> array("Du Bist Weltmeister!");

			alg::ShiftElements(array.begin(), array.begin() + 5, 0);

			Assert::AreEqual(std::string{ "Du Bist Weltmeister!" }, util::ToString(array));
		}

		TEST_METHOD(ShiftingEmptySequenceDoesNothing)
		{
			ds::Array<char> array("Thirty years ago...");

			alg::ShiftElements(array.begin() + 5, array.begin() + 5, 0);

			Assert::AreEqual(std::string{ "Thirty years ago..." }, util::ToString(array));
		}

	};

}
