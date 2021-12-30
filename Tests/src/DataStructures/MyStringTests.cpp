#include "CppUnitTest.h"
#include "MyString.h"
#include "Array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft::VisualStudio::CppUnitTestFramework {
	template<>
	static std::wstring ToString<ds::String>(const ds::String& string) {
		std::wstringstream ss;
		for (size_t i = 0; i < string.Length(); i++) {
			ss << string[i];
		}
		return ss.str();
	}
}

namespace MyString {

	TEST_CLASS(Construction)
	{
	public:
		TEST_METHOD(ConstructWithEmptyLiteral)
		{
			ds::String string("");
			Assert::IsTrue(string.IsEmpty());
			Assert::AreEqual(size_t{ 0 }, string.Length());
		}

		TEST_METHOD(ConstructWithLiteral)
		{
			ds::String string("Valtteri, it's James.");
			Assert::IsTrue(string == "Valtteri, it's James.");
			Assert::AreEqual(size_t{ 21 }, string.Length());
		}

		TEST_METHOD(ConstructWithArray)
		{
			ds::Array<char> array(5);
			array[0] = 'D';
			array[1] = 'a';
			array[2] = 'i';
			array[3] = 's';
			array[4] = 'y';
			ds::String string(array);
			Assert::IsTrue(string == "Daisy");
			Assert::AreEqual(size_t{ 5 }, string.Length());
		}
	};

	TEST_CLASS(Indexer)
	{
	public:
		TEST_METHOD(IndexIntoString)
		{
			ds::String string("Banana Bread");
			Assert::AreEqual('B', string[0]);
			Assert::AreEqual('d', string[11]);
			Assert::AreEqual('a', string[5]);
		}
		TEST_METHOD(ModifyWithIndexer)
		{
			ds::String string("James Bond");
			string[6] = 'P';
			Assert::IsTrue(string == "James Pond");
		}
		TEST_METHOD(ThrowsIfOutOfBounds)
		{
			ds::String string("Banana Bread");
			Assert::ExpectException<std::out_of_range>([&] { string[12]; });
			Assert::ExpectException<std::out_of_range>([&] { string[20]; });
		}
	};

	TEST_CLASS(Const)
	{
	public:
		TEST_METHOD(ConstStringsCanReadWithIndex)
		{
			const ds::String string("Banana Bread");
			Assert::AreEqual('B', string[0]);
			Assert::AreEqual('d', string[11]);
			Assert::AreEqual('a', string[5]);

			//string[2] = 's';  // Shouldn't compile
		}
	};

	TEST_CLASS(Comparison)
	{
	public:
		TEST_METHOD(Equals)
		{
			const ds::String string("Miss Belle");
			const ds::String stringTwo("Miss Belle");
			Assert::AreEqual(string, stringTwo);
			Assert::IsTrue(string == stringTwo);
		}
		TEST_METHOD(NotEqual)
		{
			const ds::String string("Miss Belle");
			const ds::String badString1("MissBelle");
			const ds::String badString2("Miss Belle ");
			const ds::String badString3(" Miss Belle");
			const ds::String badString4("Miss Daisy");
			Assert::AreNotEqual(string, badString1);
			Assert::AreNotEqual(string, badString2);
			Assert::AreNotEqual(string, badString3);
			Assert::AreNotEqual(string, badString4);
			Assert::IsTrue(string != badString1);
			Assert::IsTrue(string != badString2);
			Assert::IsTrue(string != badString3);
			Assert::IsTrue(string != badString4);
		}
		TEST_METHOD(EqualsLiteral)
		{
			const ds::String string("Miss Belle");
			Assert::IsTrue(string == "Miss Belle");
			Assert::IsTrue(string == "Miss Belle");
		}
		TEST_METHOD(NotEqualLiteral)
		{
			const ds::String string("Miss Belle");
			Assert::IsTrue(string != "Miss Daisy");
			Assert::IsTrue(string != "Miss Bell");
			Assert::IsTrue(string != "Miss Belle ");
			Assert::IsTrue(string != " Miss Belle");
		}
	};

}
