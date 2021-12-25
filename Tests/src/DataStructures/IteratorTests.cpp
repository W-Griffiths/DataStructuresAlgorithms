#include "CppUnitTest.h"
#include "List.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Iterators {

	TEST_CLASS(RandomAccess)
	{
	public:
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
	};

}
