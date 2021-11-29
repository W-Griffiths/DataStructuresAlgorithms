#include "CppUnitTest.h"
#include "HashTable.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashTable {

	TEST_CLASS(Construction)
	{
	public:

		TEST_METHOD(DefaultConstructed)
		{
			ds::HashTable<char, int> table;
		}

	};

	TEST_CLASS(Indexers)
	{
	public:

		TEST_METHOD(AddingValues)
		{
			ds::HashTable<std::string, int> highScores;
			highScores["Daisy"] = 100;
			highScores["Belle"] = 99;
			highScores["Will"] = 78;
		}

		TEST_METHOD(GettingNonexistentValueThrows)
		{
			ds::HashTable<std::string, int> highScores;
			highScores["Daisy"] = 100;
			highScores["Belle"] = 99;
			highScores["Daisy"];

			Assert::ExpectException<std::invalid_argument>(highScores["Will"]);
		}

	};

}
