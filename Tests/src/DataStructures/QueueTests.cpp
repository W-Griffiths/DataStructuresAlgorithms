#include "CppUnitTest.h"
#include "Queue.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Queue {

	TEST_CLASS(Construction)
	{
	public:
		TEST_METHOD(EmptyOnConstruction)
		{
			ds::Queue<int> queue;
			Assert::IsTrue(queue.IsEmpty());
			Assert::AreEqual(size_t{ 0 }, queue.Size());
		}
	};

	TEST_CLASS(Adding)
	{
	public:
		TEST_METHOD(PushingIncreasesStack)
		{
			ds::Queue<std::string> queue;

			queue.Enqueue("Hello");
			Assert::AreEqual(size_t{ 1 }, queue.Size());
			queue.Enqueue("World");
			Assert::AreEqual(size_t{ 2 }, queue.Size());
			queue.Enqueue("Daisy");
			queue.Enqueue("Daisy");
			Assert::AreEqual(size_t{ 4 }, queue.Size());
			queue.Enqueue("Give");
			queue.Enqueue("Me");
			queue.Enqueue("Your");
			queue.Enqueue("Answer");
			queue.Enqueue("Do");
			Assert::AreEqual(size_t{ 9 }, queue.Size());
		}
	};

	TEST_CLASS(Removing)
	{
	public:
		TEST_METHOD(PoppingReducesStack)
		{
			ds::Queue<int> queue;

			queue.Enqueue(55);
			queue.Enqueue(16);
			queue.Enqueue(77);
			queue.Enqueue(44);
			queue.Enqueue(11);
			queue.Enqueue(33);

			Assert::AreEqual(size_t{ 6 }, queue.Size());

			int carlos = queue.Dequeue();
			Assert::AreEqual(size_t{ 5 }, queue.Size());
			Assert::AreEqual(55, carlos);

			int charles = queue.Dequeue();
			Assert::AreEqual(size_t{ 4 }, queue.Size());
			Assert::AreEqual(16, charles);

			int valtteri = queue.Dequeue();
			int lewis = queue.Dequeue();
			int sergio = queue.Dequeue();

			int max = queue.Dequeue();
			Assert::AreEqual(size_t{ 0 }, queue.Size());
			Assert::IsTrue(queue.IsEmpty());
			Assert::AreEqual(33, max);

		}

		TEST_METHOD(PeekingDoesntReduceSize)
		{
			ds::Queue<int> queue;

			queue.Enqueue(33);
			queue.Enqueue(11);
			queue.Enqueue(44);
			queue.Enqueue(77);
			queue.Enqueue(16);
			queue.Enqueue(55);

			Assert::AreEqual(size_t{ 6 }, queue.Size());

			int max = queue.Peek();
			Assert::AreEqual(size_t{ 6 }, queue.Size());
			Assert::AreEqual(33, max);

			queue.Dequeue();
			Assert::AreEqual(size_t{ 5 }, queue.Size());

			int sergio = queue.Peek();
			Assert::AreEqual(size_t{ 5 }, queue.Size());
			Assert::AreEqual(11, sergio);
		}
	};

	TEST_CLASS(Exceptions)
	{
	public:
		TEST_METHOD(PoppingEmptyStackThrows)
		{
			ds::Queue<int> queue;

			Assert::ExpectException<std::out_of_range>([&] {queue.Dequeue(); });
		}

		TEST_METHOD(PeekingEmptyStackThrows)
		{
			ds::Queue<int> queue;

			Assert::ExpectException<std::out_of_range>([&] {queue.Peek(); });
		}
	};

}
