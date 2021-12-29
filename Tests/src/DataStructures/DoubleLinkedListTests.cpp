#include "CppUnitTest.h"
#include "DoubleLinkedList.h"
#include "ReferenceCounter.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoubleLinkedList {

	TEST_CLASS(Construction)
	{
	public:

		TEST_METHOD(DefaultConstructed)
		{
			ds::DoubleLinkedList<int> list;
			Assert::IsTrue(list.IsEmpty());
		}

	};

	TEST_CLASS(Adding)
	{
	public:

		TEST_METHOD(PushingBack)
		{
			ds::DoubleLinkedList<int> list;
			list.PushBack(44);
			list.PushBack(33);
			list.PushBack(16);
			list.PushBack(5);

			auto iter = list.begin();

			Assert::AreEqual(44, *iter);
			++iter;
			Assert::AreEqual(33, *iter);
			++iter;
			Assert::AreEqual(16, *iter);
			++iter;
			Assert::AreEqual(5, *iter);
		}

		TEST_METHOD(PushingFront)
		{
			ds::DoubleLinkedList<int> list;
			list.PushFront(44);
			list.PushFront(33);
			list.PushFront(16);
			list.PushFront(5);

			auto iter = list.begin();

			Assert::AreEqual(5, *iter);
			++iter;
			Assert::AreEqual(16, *iter);
			++iter;
			Assert::AreEqual(33, *iter);
			++iter;
			Assert::AreEqual(44, *iter);
		}

		TEST_METHOD(Push)
		{
			ds::DoubleLinkedList<int> list;
			list.PushFront(44);
			list.PushFront(33);
			list.PushBack(16);
			list.PushBack(55);
			list.PushFront(5);
			list.PushBack(11);
			list.PushFront(10);

			auto iter = list.begin();

			Assert::AreEqual(10, *iter);
			++iter;
			Assert::AreEqual(5, *iter);
			++iter;
			Assert::AreEqual(33, *iter);
			++iter;
			Assert::AreEqual(44, *iter);
			++iter;
			Assert::AreEqual(16, *iter);
			++iter;
			Assert::AreEqual(55, *iter);
			++iter;
			Assert::AreEqual(11, *iter);
		}

	};

	TEST_CLASS(Removing)
	{
	public:

		TEST_METHOD(PoppingBack)
		{
			ds::DoubleLinkedList<int> list;
			list.PushBack(44);
			list.PushBack(33);
			list.PushFront(16);
			list.PushFront(5);

			int pop = list.PopBack();
			Assert::AreEqual(33, pop);
			pop = list.PopBack();
			Assert::AreEqual(44, pop);
			pop = list.PopBack();
			Assert::AreEqual(16, pop);
			pop = list.PopBack();
			Assert::AreEqual(5, pop);
		}

		TEST_METHOD(PoppingFront)
		{
			ds::DoubleLinkedList<int> list;
			list.PushBack(44);
			list.PushBack(33);
			list.PushFront(16);
			list.PushFront(5);

			int pop = list.PopFront();
			Assert::AreEqual(5, pop);
			pop = list.PopFront();
			Assert::AreEqual(16, pop);
			pop = list.PopFront();
			Assert::AreEqual(44, pop);
			pop = list.PopFront();
			Assert::AreEqual(33, pop);
		}

		TEST_METHOD(PopToEmptyAndGrowAgain)
		{
			ds::DoubleLinkedList<int> list;
			list.PushBack(44);
			list.PushBack(33);
			list.PushFront(16);
			list.PushFront(5);

			int pop = list.PopBack();
			Assert::AreEqual(33, pop);
			pop = list.PopBack();
			Assert::AreEqual(44, pop);
			pop = list.PopBack();
			Assert::AreEqual(16, pop);
			pop = list.PopBack();
			Assert::AreEqual(5, pop);

			Assert::IsTrue(list.IsEmpty());

			list.PushBack(44);
			list.PushBack(33);
			list.PushFront(16);
			list.PushFront(5);

			pop = list.PopBack();
			Assert::AreEqual(33, pop);
			pop = list.PopBack();
			Assert::AreEqual(44, pop);
			pop = list.PopBack();
			Assert::AreEqual(16, pop);
			pop = list.PopBack();
			Assert::AreEqual(5, pop);

			Assert::IsTrue(list.IsEmpty());

			list.PushBack(0);
			Assert::IsFalse(list.IsEmpty());
		}

		TEST_METHOD(PeekingBack)
		{
			ds::DoubleLinkedList<int> list;
			list.PushBack(44);
			list.PushBack(33);
			list.PushFront(16);
			list.PushFront(5);

			Assert::AreEqual(33, list.PeekBack());
			list.PopBack();
			Assert::AreEqual(44, list.PeekBack());
			list.PopBack();
			Assert::AreEqual(16, list.PeekBack());
			list.PopBack();
			Assert::AreEqual(5, list.PeekBack());
		}

		TEST_METHOD(PeekingFront)
		{
			ds::DoubleLinkedList<int> list;
			list.PushBack(44);
			list.PushBack(33);
			list.PushFront(16);
			list.PushFront(5);

			Assert::AreEqual(5, list.PeekFront());
			list.PopFront();
			Assert::AreEqual(16, list.PeekFront());
			list.PopFront();
			Assert::AreEqual(44, list.PeekFront());
			list.PopFront();
			Assert::AreEqual(33, list.PeekFront());
		}

	};

	TEST_CLASS(Lifetime)
	{
	public:

		TEST_METHOD(PushAndPopStrings)
		{
			
			ds::DoubleLinkedList<std::string> list;

			const int size = 10;
			for (int i = 0; i < size; i++)
			{
				list.PushBack(std::to_string(i));
			}

			{
				std::string name = "Daisy";
				list.PushBack(name);
			}

			Assert::IsFalse(list.IsEmpty());

			for (int i = 0; i < size; i++)
			{
				Assert::AreEqual(std::to_string(i), list.PopFront());
			}
			
			Assert::AreEqual(std::string("Daisy"), list.PopFront());
		}
		
		/*TEST_METHOD(DestructorsFire)
		{
			int* refCount = new int{ 0 };
			{
				ds::DoubleLinkedList<ReferenceCounter> counters;
				counters.PushBack(refCount);
				Assert::AreEqual(1, *refCount);
				counters.PushBack(refCount);
				Assert::AreEqual(2, *refCount);
			}
			Assert::AreEqual(0, *refCount);
		}*/

	};

	TEST_CLASS(Iterators)
	{
	public:

		TEST_METHOD(RangeForLoop)
		{
			ds::DoubleLinkedList<int> nums;
			nums.PushBack(1);
			nums.PushBack(2);
			nums.PushBack(3);
			nums.PushBack(4);
			nums.PushBack(5);
			nums.PushBack(5);
			nums.PushBack(4);
			nums.PushBack(3);
			nums.PushBack(2);
			nums.PushBack(1);

			int sum = 0;
			for (auto& num : nums) {
				sum += num;
			}

			Assert::AreEqual(30, sum);
		}

		TEST_METHOD(ForLoop)
		{
			ds::DoubleLinkedList<int> nums;
			nums.PushBack(1);
			nums.PushBack(2);
			nums.PushBack(3);
			nums.PushBack(4);
			nums.PushBack(5);

			int sum = 0;
			for (auto& it = nums.begin(); it != nums.end(); it++)
			{
				sum += *it;
			}

			Assert::AreEqual(15, sum);
		}

	};

}
