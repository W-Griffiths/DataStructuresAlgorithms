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

	TEST_CLASS(StringComparison)
	{
	public:
		TEST_METHOD(SameStringsAreEqual)
		{
			const ds::String string("Miss Belle");
			const ds::String stringTwo("Miss Belle");
			Assert::AreEqual(string, stringTwo);
			Assert::IsTrue(string == stringTwo);
			Assert::IsFalse(string != stringTwo);
		}
		TEST_METHOD(DifferentStringAreNotEqual)
		{
			const ds::String string("Miss Belle");
			const ds::String badString1("MissBelle");
			const ds::String badString2("Miss Belle ");
			const ds::String badString3(" Miss Belle");
			const ds::String badString4("Miss Daisy");
			const ds::String badString5("Miss B");
			Assert::AreNotEqual(string, badString1);
			Assert::AreNotEqual(string, badString2);
			Assert::AreNotEqual(string, badString3);
			Assert::AreNotEqual(string, badString4);
			Assert::AreNotEqual(string, badString5);

			Assert::IsTrue(string != badString1);
			Assert::IsTrue(string != badString2);
			Assert::IsTrue(string != badString3);
			Assert::IsTrue(string != badString4);
			Assert::IsTrue(string != badString5);

			Assert::IsTrue(badString1 != string);
			Assert::IsTrue(badString2 != string);
			Assert::IsTrue(badString3 != string);
			Assert::IsTrue(badString4 != string);
			Assert::IsTrue(badString5 != string);

			Assert::IsFalse(string == badString1);
			Assert::IsFalse(string == badString2);
			Assert::IsFalse(string == badString3);
			Assert::IsFalse(string == badString4);
			Assert::IsFalse(string == badString5);

			Assert::IsFalse(badString1 == string);
			Assert::IsFalse(badString2 == string);
			Assert::IsFalse(badString3 == string);
			Assert::IsFalse(badString4 == string);
			Assert::IsFalse(badString5 == string);
		}
		TEST_METHOD(LessThan)
		{
			const ds::String string1("Ursa Major");
			const ds::String string2("Ursa Minor");

			Assert::IsTrue(string1 < string2);
			Assert::IsFalse(string2 < string1);
		}
		TEST_METHOD(GreaterThan)
		{
			const ds::String string1("Ursa Minor");
			const ds::String string2("Ursa Major");

			Assert::IsTrue(string1 > string2);
			Assert::IsFalse(string2 > string1);
		}
		TEST_METHOD(ShorterStringsAreLessThan)
		{
			const ds::String string1("aqua");
			const ds::String string2("aquamarine");

			Assert::IsTrue(string1 < string2);
			Assert::IsFalse(string2 < string1);
		}
		TEST_METHOD(LongerStringsAreGreaterThan)
		{
			const ds::String string1("aquamarine");
			const ds::String string2("aqua");

			Assert::IsTrue(string1 > string2);
			Assert::IsFalse(string2 > string1);
		}
		TEST_METHOD(UpperCaseIsLess)
		{
			const ds::String string1("Ursa Minor");
			const ds::String string2("ursa Major");

			Assert::IsTrue(string1 < string2);
			Assert::IsFalse(string2 < string1);
		}
		TEST_METHOD(LowerCaseIsGreater)
		{
			const ds::String string1("ursa Major");
			const ds::String string2("Ursa Minor");

			Assert::IsTrue(string1 > string2);
			Assert::IsFalse(string2 > string1);
		}
		TEST_METHOD(EqualStringsAreNotLessThan)
		{
			const ds::String string1("Ursa Minor");
			const ds::String string2("Ursa Minor");
			
			Assert::IsFalse(string1 < string2);
		}
		TEST_METHOD(EqualStringsAreLessThanOrEqual)
		{
			const ds::String string1("Ursa Minor");
			const ds::String string2("Ursa Minor");

			Assert::IsTrue(string1 <= string2);
			Assert::IsTrue(string2 <= string1);
		}
		TEST_METHOD(EqualStringsAreNotGreaterThan)
		{
			const ds::String string1("Ursa Major");
			const ds::String string2("Ursa Major");

			Assert::IsFalse(string1 > string2);
		}
		TEST_METHOD(EqualStringsAreGreaterThanOrEqual)
		{
			const ds::String string1("Ursa Major");
			const ds::String string2("Ursa Major");

			Assert::IsTrue(string1 >= string2);
		}
	};

	TEST_CLASS(CStringComparison)
	{
	public:
		TEST_METHOD(SameStringsAreEqual)
		{
			const ds::String string("Miss Belle");
			Assert::IsTrue (string == "Miss Belle");
			Assert::IsFalse(string != "Miss Belle");
		}
		TEST_METHOD(DifferentStringAreNotEqual)
		{
			const ds::String string("Miss Belle");

			Assert::IsTrue(string != "MissBelle");
			Assert::IsTrue(string != "Miss Belle ");
			Assert::IsTrue(string != " Miss Belle");
			Assert::IsTrue(string != "Miss Daisy");
			Assert::IsTrue(string != "Miss Bel");

			Assert::IsFalse(string == "MissBelle");
			Assert::IsFalse(string == "Miss Belle ");
			Assert::IsFalse(string == " Miss Belle");
			Assert::IsFalse(string == "Miss Daisy");
			Assert::IsFalse(string == "Miss Bel");
		}
		TEST_METHOD(LessThan)
		{
			const ds::String string("Ursa Major");

			Assert::IsTrue(string < "Ursa Minor");
		}
		TEST_METHOD(GreaterThan)
		{
			const ds::String string("Ursa Minor");

			Assert::IsTrue(string > "Ursa Major");
		}
		TEST_METHOD(ShorterStringsAreLessThan)
		{
			const ds::String string("aqua");

			Assert::IsTrue(string < "aquamarine");
		}
		TEST_METHOD(LongerStringsAreGreaterThan)
		{
			const ds::String string("aquamarine");

			Assert::IsTrue(string > "aqua");
		}
		TEST_METHOD(UpperCaseIsLess)
		{
			const ds::String string("Ursa Minor");

			Assert::IsTrue(string < "ursa Major");
		}
		TEST_METHOD(LowerCaseIsGreater)
		{
			const ds::String string("ursa Major");

			Assert::IsTrue(string > "Ursa Minor");
		}
		TEST_METHOD(EqualStringsAreNotLessThan)
		{
			const ds::String string("Ursa Minor");

			Assert::IsFalse(string < "Ursa Minor");
		}
		TEST_METHOD(EqualStringsAreLessThanOrEqual)
		{
			const ds::String string("Ursa Minor");

			Assert::IsTrue(string <= "Ursa Minor");
		}
		TEST_METHOD(EqualStringsAreNotGreaterThan)
		{
			const ds::String string("Ursa Major");

			Assert::IsFalse(string > "Ursa Major");
		}
		TEST_METHOD(EqualStringsAreGreaterThanOrEqual)
		{
			const ds::String string("Ursa Major");

			Assert::IsTrue(string >= "Ursa Major");
		}
	};

}
