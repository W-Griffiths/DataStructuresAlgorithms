#include "CppUnitTest.h"
#include "LinkedList.h"
#include "ReferenceCounter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LinkedList {

	TEST_CLASS(Construction)
	{
	public:

		TEST_METHOD(DefaultConstructed)
		{
			ds::LinkedList<int> list;
		}

	};

	TEST_CLASS(Lifetime)
	{
	public:

		TEST_METHOD(DestructorsFire)
		{
			int* refCount = new int{ 0 };
			{
				ds::LinkedList<ReferenceCounter> counters;
				counters.Insert({ refCount });
				Assert::AreEqual(1, *refCount);
				counters.Insert({ refCount });
				Assert::AreEqual(2, *refCount);
			}
			Assert::AreEqual(0, *refCount);
		}

	};

	TEST_CLASS(Iterators)
	{
	public:

		TEST_METHOD(RangeForLoop)
		{
			ds::LinkedList<int> nums;
			nums.Insert(1);
			nums.Insert(2);
			nums.Insert(3);
			nums.Insert(4);
			nums.Insert(5);

			int sum = 0;
			for (auto& num : nums) {
				sum += num;
			}

			Assert::AreEqual(15, sum);
		}

		TEST_METHOD(ForLoop)
		{
			ds::LinkedList<int> nums;
			nums.Insert(1);
			nums.Insert(2);
			nums.Insert(3);
			nums.Insert(4);
			nums.Insert(5);

			int sum = 0;
			for (auto& it = nums.begin(); it != nums.end(); it++)
			{
				sum += *it;
			}

			Assert::AreEqual(15, sum);
		}

	};

}
