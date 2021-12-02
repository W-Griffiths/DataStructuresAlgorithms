#include "CppUnitTest.h"
#include "HashSet.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashSet {

	TEST_CLASS(Construction)
	{
	public:

		TEST_METHOD(DefaultConstructed)
		{
			ds::HashSet<int> set;

			int sum = 0;
			for (auto& item : set) {
				sum += item;
			}

			Assert::AreEqual(0, sum);
		}

	};

	TEST_CLASS(Add)
	{
	public:

		TEST_METHOD(AddUnique)
		{
			ds::HashSet<int> numbers;
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

		TEST_METHOD(DuplicatesAreIgnored)
		{
			ds::HashSet<int> numbers;
			numbers.Add(33);
			numbers.Add(33);
			numbers.Add(33);
			numbers.Add(44);
			numbers.Add(44);

			Assert::IsTrue(numbers.Contains(33));
			Assert::IsTrue(numbers.Contains(44));

			int sum = 0;
			for (auto& num : numbers) {
				sum += num;
			}

			Assert::AreEqual(77, sum);
		}

		TEST_METHOD(DuplicatesReturnFalse)
		{
			ds::HashSet<int> numbers;
			numbers.Add(33);
			numbers.Add(44);
			numbers.Add(77);

			Assert::IsTrue(numbers.Contains(33));
			Assert::IsTrue(numbers.Contains(44));
			Assert::IsTrue(numbers.Contains(77));

			Assert::IsFalse(numbers.TryAdd(33));
			Assert::IsFalse(numbers.TryAdd(44));
			Assert::IsFalse(numbers.TryAdd(77));
		}

	};

}
