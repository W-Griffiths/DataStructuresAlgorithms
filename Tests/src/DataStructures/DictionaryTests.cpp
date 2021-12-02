#include "CppUnitTest.h"
#include "Dictionary.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Dictionary {

	TEST_CLASS(Construction)
	{
	public:

		TEST_METHOD(DefaultConstructed)
		{
			ds::Dictionary<std::string, int> dictionary;
		}

	};

	TEST_CLASS(Iterator)
	{
	public:

		TEST_METHOD(RangeForLoop)
		{
			ds::Dictionary<std::string, int> highScores;
			highScores["Daisy"] = 100;
			highScores["Belle"] = 99;
			highScores["Will"] = 78;

			int totalScore = 0;
			for (auto score : highScores) {
				totalScore += score.value;
			}

			Assert::AreEqual(277, totalScore);
		}

	};

	TEST_CLASS(Contains)
	{
	public:

		TEST_METHOD(ContainedValuesReturnTrue)
		{
			ds::Dictionary<std::string, int> highScores;
			highScores["Daisy"] = 100;
			highScores["Belle"] = 99;
			highScores["Will"] = 78;

			

			Assert::IsTrue(highScores.Contains("Daisy"));
			Assert::IsTrue(highScores.Contains("Will"));
		}

		TEST_METHOD(NonexistantValuesReturnFalse)
		{
			ds::Dictionary<std::string, int> highScores;
			highScores["Daisy"] = 100;
			highScores["Belle"] = 99;
			highScores["Will"] = 78;

			Assert::IsFalse(highScores.Contains("Laura"));
			Assert::IsFalse(highScores.Contains("Archie"));
		}

	};

	TEST_CLASS(Indexers)
	{
	public:

		TEST_METHOD(AddingValues)
		{
			ds::Dictionary<std::string, int> highScores;
			highScores["Daisy"] = 100;
			highScores["Belle"] = 99;
			highScores["Will"] = 78;
		}

		TEST_METHOD(IndexingStrings)
		{
			using namespace std::literals::string_literals;
			
			ds::Dictionary<std::string, std::string> teams;
			teams["Verstappen"] = "Red Bull";
			teams["Leclerc"] = "Ferrari";
			teams["Hamilton"] = "Mercedes";

			Assert::AreEqual("Red Bull"s, teams["Verstappen"]);
			Assert::AreEqual("Ferrari"s, teams["Leclerc"]);
			Assert::AreEqual("Mercedes"s, teams["Hamilton"]);
		}

		TEST_METHOD(GettingValues)
		{
			ds::Dictionary<std::string, int> highScores;
			highScores["Daisy"] = 100;
			highScores["Belle"] = 99;
			highScores["Will"] = 78;

			Assert::AreEqual(100, highScores["Daisy"]);
			Assert::AreEqual(99, highScores["Belle"]);
		}

		/*TEST_METHOD(GettingNonexistentValueThrows)
		{
			ds::Dictionary<std::string, int> highScores;
			highScores["Daisy"] = 100;
			highScores["Belle"] = 99;

			const auto cHS = highScores;

			Assert::AreEqual(100, cHS["Daisy"]);
			Assert::ExpectException<std::invalid_argument>([&] { cHS["Will"]; });
		}*/

	};

}
