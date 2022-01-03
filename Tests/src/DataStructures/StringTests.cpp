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

namespace String {

	TEST_CLASS(Construction)
	{
	public:
		TEST_METHOD(ConstructWithEmptyLiteral)
		{
			ds::String string("");
			Assert::IsTrue(string.IsEmpty());
			Assert::AreEqual(size_t{ 0 }, string.Length());

			Assert::IsTrue(string == "");
			Assert::AreEqual({ "" }, string);
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

		TEST_METHOD(CopyConstruct)
		{
			ds::String red16("Leclerc");
			ds::String fast(red16);

			Assert::AreEqual(red16, fast);
			Assert::AreEqual({ "Leclerc" }, red16);
			Assert::AreEqual({ "Leclerc" }, fast);
			Assert::IsTrue(fast == "Leclerc");

			red16[2] = 'g';
			red16[6] = 'g';

			Assert::AreNotEqual(red16, fast);
			Assert::AreEqual({ "Leglerg" }, red16);
			Assert::AreEqual({ "Leclerc" }, fast);
			Assert::IsTrue(fast == "Leclerc");
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

	TEST_CLASS(EmptyOrWhitespace)
	{
	public:
		TEST_METHOD(EmptyStringsPass)
		{
			const ds::String string = ds::String::Empty();

			Assert::IsTrue(string.IsEmptyOrWhitespace());
		}
		TEST_METHOD(WhitespaceStringsPass)
		{
			const ds::String string1(" ");
			Assert::IsTrue(string1.IsEmptyOrWhitespace());

			const ds::String string2("     ");
			Assert::IsTrue(string2.IsEmptyOrWhitespace());

			const ds::String string3(" \t \t\t \n    ");
			Assert::IsTrue(string3.IsEmptyOrWhitespace());
		}
		TEST_METHOD(StringsWithNonWhitespaceFail)
		{
			const ds::String string("  \n  hi   ");

			Assert::IsFalse(string.IsEmptyOrWhitespace());
		}
	};

	TEST_CLASS(Append)
	{
	public:
		TEST_METHOD(AppendingStrings)
		{
			const ds::String string("Daisy");
			const ds::String string2(", Daisy");
			const ds::String string3(", give me your answer do.");

			const ds::String result1 = string.Append(string2);
			Assert::AreEqual({"Daisy, Daisy"}, result1);
			Assert::AreEqual({"Daisy"}, string);
			
			const ds::String result2 = result1.Append(string3);
			Assert::AreEqual({ "Daisy, Daisy, give me your answer do." }, result2);
		}
		TEST_METHOD(AppendingCStrings)
		{
			const ds::String string("Daisy");

			const ds::String result1 = string.Append(", Daisy");
			Assert::AreEqual({ "Daisy, Daisy" }, result1);
			Assert::AreEqual({ "Daisy" }, string);

			const ds::String result2 = result1.Append(", give me your answer do.");
			Assert::AreEqual({ "Daisy, Daisy, give me your answer do." }, result2);
		}
		TEST_METHOD(AppendEmptyString)
		{
			const ds::String string("Hornet");
			const ds::String string2("");

			const ds::String result1 = string.Append(string2);
			Assert::AreEqual({ "Hornet" }, result1);
		}
		TEST_METHOD(AppendEmptyCString)
		{
			const ds::String string("Hornet");

			const ds::String result1 = string.Append("");
			Assert::AreEqual({ "Hornet" }, result1);
		}
	};

	TEST_CLASS(ToUpper)
	{
	public:
		TEST_METHOD(ConvertsToUpperCase)
		{
			const ds::String original("Greenpath");
			ds::String string("Greenpath");

			Assert::AreEqual(original, string);

			string.ToUpper();
			const ds::String target("GREENPATH");

			Assert::AreEqual(target, string);
			Assert::AreNotEqual(original, string);
		}

		TEST_METHOD(ConstReturnsNewString)
		{
			const ds::String original("Greenpath");
			const ds::String string("Greenpath");
			const ds::String target("GREENPATH");

			Assert::AreEqual(original, string);

			const ds::String result = string.ToUpper();

			Assert::AreEqual(original, string);
			Assert::AreNotEqual(target, string);
			Assert::AreEqual(target, result);
		}

		TEST_METHOD(SymbolsAndSpacesPass)
		{
			const ds::String original("It's lights out, and away we go!");
			ds::String string("It's lights out, and away we go!");

			Assert::AreEqual(original, string);

			string.ToUpper();
			const ds::String target("IT'S LIGHTS OUT, AND AWAY WE GO!");

			Assert::AreEqual(target, string);
			Assert::AreNotEqual(original, string);
		}

		TEST_METHOD(EmptyStringsDontChange)
		{
			const ds::String original("");
			ds::String string("");

			Assert::AreEqual(original, string);

			string.ToUpper();
			Assert::AreEqual(original, string);
		}

		TEST_METHOD(AllUpperCaseStringsDontChange)
		{
			const ds::String original("HAL 9000");
			ds::String string("HAL 9000");

			Assert::AreEqual(original, string);

			string.ToUpper();
			Assert::AreEqual(original, string);
		}
	};

	TEST_CLASS(ToLower)
	{
	public:
		TEST_METHOD(ConvertsToLowerCase)
		{
			const ds::String original("Queen's Gardens");
			ds::String string("Queen's Gardens");

			Assert::AreEqual(original, string);

			string.ToLower();
			const ds::String target("queen's gardens");

			Assert::AreEqual(target, string);
			Assert::AreNotEqual(original, string);
		}

		TEST_METHOD(ConstReturnsNewString)
		{
			const ds::String original("Queen's Gardens");
			const ds::String string("Queen's Gardens");
			const ds::String target("queen's gardens");

			Assert::AreEqual(original, string);

			const ds::String result = string.ToLower();

			Assert::AreEqual(original, string);
			Assert::AreNotEqual(target, string);
			Assert::AreEqual(target, result);
		}

		TEST_METHOD(SymbolsAndSpacesPass)
		{
			const ds::String original("Higher beings, these words are for you alone.");
			ds::String string("Higher beings, these words are for you alone.");

			Assert::AreEqual(original, string);

			string.ToLower();
			const ds::String target("higher beings, these words are for you alone.");

			Assert::AreEqual(target, string);
			Assert::AreNotEqual(original, string);
		}

		TEST_METHOD(EmptyStringsDontChange)
		{
			const ds::String original("");
			ds::String string("");

			Assert::AreEqual(original, string);

			string.ToLower();
			Assert::AreEqual(original, string);
		}

		TEST_METHOD(AllLowerCaseStringsDontChange)
		{
			const ds::String original("the last stag");
			ds::String string("the last stag");

			Assert::AreEqual(original, string);

			string.ToLower();
			Assert::AreEqual(original, string);
		}
	};

	TEST_CLASS(Alphabetic)
	{
	public:
		TEST_METHOD(LettersAndSpacesAreAlphabetic)
		{
			const ds::String string1("Fog Canyon");
			Assert::IsTrue(string1.IsAlphabetic());

			const ds::String string2("Willoh");
			Assert::IsTrue(string2.IsAlphabetic());
		}

		TEST_METHOD(SymbolsAndNumbersAreNotAlphabetic)
		{
			const ds::String string1("Kingdom's Edge");
			Assert::IsFalse(string1.IsAlphabetic());

			const ds::String string2("Valterri, it's James.");
			Assert::IsFalse(string2.IsAlphabetic());

			const ds::String string3("HAL 9000");
			Assert::IsFalse(string3.IsAlphabetic());
		}

		TEST_METHOD(EmptyOrWhitespaceStringsFail)
		{
			const ds::String emptyString = ds::String::Empty();
			Assert::IsFalse(emptyString.IsAlphabetic());

			const ds::String whitespace("   \n ");
			Assert::IsFalse(whitespace.IsAlphabetic());
		}

	};
	
	TEST_CLASS(AlphaNumeric)
	{
	public:
		TEST_METHOD(LettersNumbersAndSpacesAreAlphaNumeric)
		{
			const ds::String string1("HAL 9000");
			Assert::IsTrue(string1.IsAlphaNumeric());

			const ds::String string2("Willoh");
			Assert::IsTrue(string2.IsAlphaNumeric());

			const ds::String string3("R3d Bu11");
			Assert::IsTrue(string3.IsAlphaNumeric());
		}

		TEST_METHOD(SymbolsAreNotAlphaNumeric)
		{
			const ds::String string1("Kingdom's Edge");
			Assert::IsFalse(string1.IsAlphaNumeric());

			const ds::String string2("Valterri, it's James.");
			Assert::IsFalse(string2.IsAlphaNumeric());

			const ds::String string3("Marks & Spencer");
			Assert::IsFalse(string3.IsAlphaNumeric());
		}

		TEST_METHOD(EmptyOrWhitespaceStringsFail)
		{
			const ds::String emptyString = ds::String::Empty();
			Assert::IsFalse(emptyString.IsAlphaNumeric());

			const ds::String whitespace("   \n ");
			Assert::IsFalse(whitespace.IsAlphaNumeric());
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

	TEST_CLASS(EmptyString)
	{
	public:
		TEST_METHOD(EmptyStringIsEmpty)
		{
			const ds::String string = ds::String::Empty();

			Assert::IsTrue(string.IsEmpty());
			Assert::AreEqual({ "" }, string);
			Assert::IsTrue(string == "");
		}
	};

	TEST_CLASS(Iterator)
	{
	public:
		TEST_METHOD(ForEachLoop)
		{
			const ds::String string("Millibelle the Banker");

			int numVowels = 0;
			for (auto c : string) {
				if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
					numVowels++;
				}
			}

			Assert::AreEqual(7, numVowels);
		}
		TEST_METHOD(ForEachLoopWithEmptyString)
		{
			const ds::String string = ds::String::Empty();

			int numLetters = 0;
			for (auto c : string) {
				numLetters++;
			}

			Assert::AreEqual(0, numLetters);
		}
	};

}
