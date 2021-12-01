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
			ds::HashTable<int> table;
		}

	};

	TEST_CLASS(Add)
	{
	public:

		TEST_METHOD(AddUnique)
		{
			ds::HashTable<int> numbers;
			numbers.Add(33);
			numbers.Add(44);
			numbers.Add(77);
			numbers.Add(16);
			numbers.Add(5);

			Assert::IsTrue(numbers.Contains(33));
			Assert::IsTrue(numbers.Contains(44));
			Assert::IsTrue(numbers.Contains(77));
			Assert::IsTrue(numbers.Contains(16));
			Assert::IsTrue(numbers.Contains(5));
		}

		TEST_METHOD(AddDuplicates)
		{
			ds::HashTable<int> numbers;
			numbers.Add(33);
			numbers.Add(33);
			numbers.Add(33);

			Assert::IsTrue(numbers.Contains(33));
		}

		TEST_METHOD(TableShouldResize)
		{
			ds::HashTable<int> table;
			
			for (int i = 0; i < 1000; i++)
			{
				table.Add(i);
			}

			Assert::IsTrue(table.Contains(1));
			Assert::IsTrue(table.Contains(500));
			Assert::IsTrue(table.Contains(999));
		}

	};

	TEST_CLASS(Iterator)
	{
	public:

		TEST_METHOD(RangeForLoop)
		{
			ds::HashTable<int> numbers;
			numbers.Add(33);
			numbers.Add(33);
			numbers.Add(33);

			int sum = 0;
			for (auto number : numbers) {
				sum += number;
			}

			Assert::AreEqual(99, sum);
		}

		TEST_METHOD(Const)
		{
			ds::HashTable<int> numbers;
			numbers.Add(33);

			auto begin = numbers.begin();

			// Should not compile
			//*begin = 3;
			//auto end = numbers.end();
			//end++;
		}

	};

	/*TEST_CLASS(Indexers)
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

	};*/

}