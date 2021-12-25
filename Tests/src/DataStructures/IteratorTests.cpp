#include "CppUnitTest.h"
#include "List.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Iterators {

	TEST_CLASS(RandomAccess)
	{
	public:
		TEST_METHOD(Indexer)
		{
			ds::List<int> list;

			for (int i = 0; i < 10; i++)
			{
				list.Add(i);
			}

			auto iter = list.begin();
			
			Assert::AreEqual(0, iter[0]);
			Assert::AreEqual(5, iter[5]);
			Assert::AreEqual(7, iter[7]);

			auto iter2 = iter + 1;
			Assert::AreEqual(iter[0], iter2[-1]);
		}
		TEST_METHOD(Comparison)
		{
			ds::List<int> list;

			for (int i = 0; i < 10; i++)
			{
				list.Add(i);
			}

			auto iter = list.begin();
			auto begin = list.begin();
			auto end = list.end();


			Assert::IsTrue(iter == begin);
			Assert::IsFalse(iter != begin);
			Assert::IsTrue(iter <= begin);
			Assert::IsTrue(iter >= begin);
			Assert::IsFalse(iter < begin);
			Assert::IsFalse(iter > begin);
			Assert::IsTrue(begin != end);

			iter++;

			Assert::IsFalse(iter == begin);
			Assert::IsTrue(iter != begin);
			Assert::IsFalse(iter <= begin);
			Assert::IsTrue(iter >= begin);
			Assert::IsFalse(iter < begin);
			Assert::IsTrue(iter > begin);

			Assert::IsFalse(iter == end);
			Assert::IsTrue(iter != end);
			Assert::IsTrue(iter <= end);
			Assert::IsFalse(iter >= end);
			Assert::IsTrue(iter < end);
			Assert::IsFalse(iter > end);
		}
		TEST_METHOD(Subtraction)
		{
			ds::List<int> list;

			for (int i = 0; i < 10; i++)
			{
				list.Add(i);
			}

			auto iter = list.begin();
			auto end = list.end();

			Assert::AreEqual(10, end-iter);

			auto iter2 = iter + 5;
			Assert::AreEqual(5, iter2 - iter);
			Assert::AreEqual(-5, iter - iter2);
		}
	};

}
