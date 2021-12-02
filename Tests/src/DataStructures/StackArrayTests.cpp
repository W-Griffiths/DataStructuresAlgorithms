#include "CppUnitTest.h"
#include "StackArray.h"
#include "Tracer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StackArray {

	TEST_CLASS(Construction)
	{
	public:
		TEST_METHOD(ConstructedWith100Capacity)
		{
			ds::StackArray<int, 100> arr;
			Assert::AreEqual(100, static_cast<int>(arr.Size()));
		}
	};

	TEST_CLASS(Indexer)
	{
	public:

		TEST_METHOD(IndexerSetsAndGets)
		{
			ds::StackArray<int, 5> arr;
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

	TEST_CLASS(Lifetime)
	{
	public:

		TEST_METHOD(TracersDestruct)
		{
			Tracer outside("Outside Tracer");
			{
				ds::StackArray<Tracer, 3> arr;
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
			ds::StackArray<int, 5> nums;
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
			ds::StackArray<int, 5> nums;
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
			ds::StackArray<int, 5> nums;
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
			ds::StackArray<int, 5> nums;
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
