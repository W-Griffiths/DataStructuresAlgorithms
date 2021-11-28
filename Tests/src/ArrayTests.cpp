#include "CppUnitTest.h"
#include "Array.h"
#include "Tracer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Array {

	TEST_CLASS(Construction)
	{
	public:

		TEST_METHOD(ConstructedWithZeroCapacity)
		{
			ds::Array<int, 0> arr;
			Assert::AreEqual(0, static_cast<int>(arr.Size()));
		}
		TEST_METHOD(ConstructedWith100Capacity)
		{
			ds::Array<int, 100> arr;
			Assert::AreEqual(100, static_cast<int>(arr.Size()));
		}
	};

	TEST_CLASS(Indexer)
	{
	public:

		TEST_METHOD(IndexerSetsAndGets)
		{
			ds::Array<int, 5> arr;
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
				ds::Array<Tracer, 3> arr;
				arr[0] = Tracer("Inside Tracer 1");
				arr[1] = Tracer("Inside Tracer 2");
				arr[2] = outside;
			}

		}
	};

}
