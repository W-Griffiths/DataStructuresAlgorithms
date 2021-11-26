#include "CppUnitTest.h"
#include "List.h"
#include "Tracer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace List {
	TEST_CLASS(Construction)
	{
	public:

		TEST_METHOD(ConstructedWithZeroCapacity)
		{
			ds::List<int> list(0);
			Assert::AreEqual(0, static_cast<int>(list.Size()));
		}
		TEST_METHOD(ConstructedWith100Capacity)
		{
			ds::List<int> list(100);
			Assert::AreEqual(0, static_cast<int>(list.Size()));
		}
	};

	TEST_CLASS(Lifetime)
	{
	public:

		TEST_METHOD(LoggingTracers)
		{
			Tracer tracerOut("Outside Tracer");
			{
				ds::List<Tracer> list;
				list.Add(Tracer("Inside Added Tracer"));
				list.Add(tracerOut);
				list[0] = Tracer("Indexed Tracer");
			}
		}
	};

	TEST_CLASS(Add)
	{
	public:

		struct Vector3 {
			Vector3()
				: x(0), y(0), z(0) {}

			Vector3(float x, float y, float z)
				: x(x), y(y), z(z) {}

			Vector3& operator=(const Vector3& other) {
				x = other.x;
				y = other.y;
				z = other.z;
				return *this;
			}

			float x, y, z;
		};

		TEST_METHOD(Add5Elements)
		{
			ds::List<int> list;
			list.Add(5);
			list.Add(8);
			list.Add(7);
			list.Add(1);
			list.Add(5);
			Assert::AreEqual(5, static_cast<int>(list.Size()));
		}
	};

	TEST_CLASS(Indexer)
	{
	public:

		TEST_METHOD(ReadingValues)
		{
			using namespace std::string_literals;

			ds::List<std::string> list(100);
			list.Add("Bach"s);
			list.Add("Chopin"s);
			list.Add("Wagner"s);
			Assert::AreEqual("Bach"s, list[0]);
			Assert::AreEqual("Chopin"s, list[1]);
			Assert::AreEqual("Wagner"s, list[2]);
		}

		TEST_METHOD(ReadinForLoop)
		{
			using namespace std::string_literals;

			ds::List<int> nums;
			nums.Add(5);
			nums.Add(10);
			nums.Add(5);
			nums.Add(10);
			nums.Add(3);
			
			int sum = 0;
			for (size_t i = 0; i < nums.Size(); i++)
			{
				sum += nums[i];
			}

			Assert::AreEqual(33, sum);
		}
	};
}
