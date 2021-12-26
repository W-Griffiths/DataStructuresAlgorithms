#include "CppUnitTest.h"
#include "Stack.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Stack {

	TEST_CLASS(Construction)
	{
	public:
		TEST_METHOD(EmptyOnConstruction)
		{
			ds::Stack<int> stack;
			Assert::IsTrue(stack.IsEmpty());
			Assert::AreEqual(size_t{ 0 }, stack.Size());
		}
	};

	TEST_CLASS(Adding)
	{
	public:
		TEST_METHOD(PushingIncreasesStack)
		{
			ds::Stack<std::string> stack;

			stack.Push("Hello");
			Assert::AreEqual(size_t{ 1 }, stack.Size());
			stack.Push("World");
			Assert::AreEqual(size_t{ 2 }, stack.Size());
			stack.Push("Daisy");
			stack.Push("Daisy");
			Assert::AreEqual(size_t{ 4 }, stack.Size());
			stack.Push("Give");
			stack.Push("Me");
			stack.Push("Your");
			stack.Push("Answer");
			stack.Push("Do");
			Assert::AreEqual(size_t{ 9 }, stack.Size());
		}
	};

	TEST_CLASS(Removing)
	{
	public:
		TEST_METHOD(PoppingReducesStack)
		{
			ds::Stack<int> stack;

			stack.Push(33);
			stack.Push(11);
			stack.Push(44);
			stack.Push(77);
			stack.Push(16);
			stack.Push(55);

			Assert::AreEqual(size_t{ 6 }, stack.Size());

			int carlos = stack.Pop();
			Assert::AreEqual(size_t{ 5 }, stack.Size());
			Assert::AreEqual(55, carlos);

			int charles = stack.Pop();
			Assert::AreEqual(size_t{ 4 }, stack.Size());
			Assert::AreEqual(16, charles);

			int valterri = stack.Pop();
			int lewis = stack.Pop();
			int sergio = stack.Pop();

			int max = stack.Pop();
			Assert::AreEqual(size_t{ 0 }, stack.Size());
			Assert::IsTrue(stack.IsEmpty());
			Assert::AreEqual(33, max);

		}

		TEST_METHOD(PeekingDoesntReduceSize)
		{
			ds::Stack<int> stack;

			stack.Push(33);
			stack.Push(11);
			stack.Push(44);
			stack.Push(77);
			stack.Push(16);
			stack.Push(55);

			Assert::AreEqual(size_t{ 6 }, stack.Size());

			int carlos = stack.Peek();
			Assert::AreEqual(size_t{ 6 }, stack.Size());
			Assert::AreEqual(55, carlos);

			stack.Pop();
			Assert::AreEqual(size_t{ 5 }, stack.Size());

			int charles = stack.Peek();
			Assert::AreEqual(size_t{ 5 }, stack.Size());
			Assert::AreEqual(16, charles);
		}
	};

	TEST_CLASS(Exceptions)
	{
	public:
		TEST_METHOD(PoppingEmptyStackThrows)
		{
			ds::Stack<int> stack;

			Assert::ExpectException<std::out_of_range>([&] {stack.Pop();});
		}

		TEST_METHOD(PeekingEmptyStackThrows)
		{
			ds::Stack<int> stack;

			Assert::ExpectException<std::out_of_range>([&] {stack.Peek();});
		}
	};

}
