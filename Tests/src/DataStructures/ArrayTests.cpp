#include "CppUnitTest.h"
#include "Array.h"
#include "Tracer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Array {

	TEST_CLASS(Construction)
	{
	public:
		TEST_METHOD(ConstructedWith100Capacity)
		{
			ds::Array<int> arr(100);
			Assert::AreEqual(100, static_cast<int>(arr.Size()));
		}
	};

	TEST_CLASS(Indexer)
	{
	public:

		TEST_METHOD(IndexerSetsAndGets)
		{
			ds::Array<int> arr(5);
			arr[0] = 5;
			arr[1] = 10;
			arr[2] = 5;
			arr[3] = 3;
			arr[4] = 10;

			int sum = 0;
			for (size_t i = 0; i < arr.Size(); i++) {
				sum += arr[i];
			}
			Assert::AreEqual(33, sum);
		}
	};

	TEST_CLASS(Equality)
	{
	public:
		TEST_METHOD(SameValuesAreEqual)
		{
			ds::Array<int> arrayA(5);
			arrayA[0] = 10;
			arrayA[1] = 20;
			arrayA[2] = 30;
			arrayA[3] = 40;
			arrayA[4] = 50;

			ds::Array<int> arrayB(5);
			arrayB[0] = 10;
			arrayB[1] = 20;
			arrayB[2] = 30;
			arrayB[3] = 40;
			arrayB[4] = 50;

			Assert::IsTrue(arrayA == arrayB);
		}

	};

	TEST_CLASS(Lifetime)
	{
	public:

		TEST_METHOD(TracersDestruct)
		{
			Tracer outside("Outside Tracer");
			{
				ds::Array<Tracer> arr(3);
				arr[0] = Tracer("Inside Tracer 1");
				arr[1] = Tracer("Inside Tracer 2");
				arr[2] = outside;
			}

		}
	};

	TEST_CLASS(Iterators)
	{
	public:

		TEST_METHOD(RangeForLoop)
		{
			ds::Array<int> nums(5);
			nums[0] = 5;
			nums[1] = 8;
			nums[2] = 7;
			nums[3] = 1;
			nums[4] = 2;

			int sum = 0;
			for (auto& num : nums)
			{
				sum += num;
			}

			Assert::AreEqual(23, sum);
		}

		TEST_METHOD(ForLoop)
		{
			ds::Array<int> nums(5);
			nums[0] = 5;
			nums[1] = 8;
			nums[2] = 7;
			nums[3] = 1;
			nums[4] = 2;

			int sum = 0;
			for (auto& it = nums.begin(); it != nums.end(); it++)
			{
				sum += *it;
			}

			Assert::AreEqual(23, sum);
		}

		TEST_METHOD(PartialIterLoop)
		{
			ds::Array<int> nums(5);
			nums[0] = 5;
			nums[1] = 8;
			nums[2] = 7;
			nums[3] = 1;
			nums[4] = 2;

			int sum = 0;
			auto it = nums.begin() + 1;
			auto end = it + 3;
			while (it != end) {
				sum += *it;
				it++;
			}

			Assert::AreEqual(16, sum);
		}

		TEST_METHOD(ReverseForLoop)
		{
			ds::Array<int> nums(5);
			nums[0] = 5;
			nums[1] = 8;
			nums[2] = 7;
			nums[3] = 1;
			nums[4] = 2;

			int sum = 0;
			for (auto& it = nums.end() - 1; it != nums.begin() - 1; it--)
			{
				sum += *it;
			}

			Assert::AreEqual(23, sum);
		}
	};

}
