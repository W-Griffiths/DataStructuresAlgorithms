#include "CppUnitTest.h"
#include "StringBuilder.h"
#include "MyString.h"

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

namespace StringBuilder {

	TEST_CLASS(Construction)
	{
	public:
		TEST_METHOD(DefaultConstructionIsEmpty)
		{
			ds::StringBuilder sb;
			Assert::IsTrue(sb.IsEmpty());
			
			const ds::String string = sb.ToString();
			Assert::IsTrue(string.IsEmpty());
			Assert::AreEqual(ds::String::Empty(), string);
		}
	};

	TEST_CLASS(Appending)
	{
	public:
		TEST_METHOD(AppendingStrings)
		{
			ds::StringBuilder sb;
			sb.Append(ds::String("April is the cruellest month, breeding\nLilacs out of the dead land,"));
			Assert::IsFalse(sb.IsEmpty());

			const ds::String target1 = "April is the cruellest month, breeding\nLilacs out of the dead land,";
			Assert::AreEqual(target1, sb.ToString());

			sb.Append(ds::String(" mixing\nMemory and desire, stirring\nDull roots with spring rain."));

			const ds::String target2 = "April is the cruellest month, breeding\nLilacs out of the dead land, mixing\nMemory and desire, stirring\nDull roots with spring rain.";
			Assert::AreEqual(target2, sb.ToString());
		}
		TEST_METHOD(AppendingSmallStrings)
		{
			ds::StringBuilder sb;
			sb.Append(ds::String("Ab"));
			sb.Append(ds::String("so"));
			sb.Append(ds::String("lute "));
			sb.Append(ds::String("Ra"));
			sb.Append(ds::String("di"));
			sb.Append(ds::String("ance"));

			const ds::String target1 = "Absolute Radiance";
			Assert::AreEqual(target1, sb.ToString());
		}
		TEST_METHOD(AppendingCStrings)
		{
			ds::StringBuilder sb;
			sb.Append("April is the cruellest month, breeding\nLilacs out of the dead land,");
			Assert::IsFalse(sb.IsEmpty());

			const ds::String target1 = "April is the cruellest month, breeding\nLilacs out of the dead land,";
			Assert::AreEqual(target1, sb.ToString());

			sb.Append(" mixing\nMemory and desire, stirring\nDull roots with spring rain.");

			const ds::String target2 = "April is the cruellest month, breeding\nLilacs out of the dead land, mixing\nMemory and desire, stirring\nDull roots with spring rain.";
			Assert::AreEqual(target2, sb.ToString());
		}
		TEST_METHOD(AppendingSingleChar)
		{
			ds::StringBuilder sb;

			const ds::String string1 = "April is the cruellest month, breeding\nLilacs out of the dead land,";
			for (char c : string1) {
				sb.Append(c);
			}

			const ds::String target1 = "April is the cruellest month, breeding\nLilacs out of the dead land,";
			Assert::AreEqual(target1, sb.ToString());

			const ds::String string2 = " mixing\nMemory and desire, stirring\nDull roots with spring rain.";
			for (char c : string2) {
				sb.Append(c);
			}

			const ds::String target2 = "April is the cruellest month, breeding\nLilacs out of the dead land, mixing\nMemory and desire, stirring\nDull roots with spring rain.";
			Assert::AreEqual(target2, sb.ToString());
		}

		TEST_METHOD(AppendingEmptyString)
		{
			ds::StringBuilder sb;
			sb.Append(ds::String("April is the cruellest month, breeding\nLilacs out of the dead land,"));
			Assert::IsFalse(sb.IsEmpty());

			const ds::String target1 = "April is the cruellest month, breeding\nLilacs out of the dead land,";
			Assert::AreEqual(target1, sb.ToString());

			sb.Append(ds::String(""));

			Assert::AreEqual(target1, sb.ToString());
		}
		TEST_METHOD(AppendingEmptyCString)
		{
			ds::StringBuilder sb;
			sb.Append("April is the cruellest month, breeding\nLilacs out of the dead land,");
			Assert::IsFalse(sb.IsEmpty());

			const ds::String target1 = "April is the cruellest month, breeding\nLilacs out of the dead land,";
			Assert::AreEqual(target1, sb.ToString());

			sb.Append("");

			Assert::AreEqual(target1, sb.ToString());
		}
	};

	TEST_CLASS(OperatorPlusEquals)
	{
	public:
		TEST_METHOD(AppendingStrings)
		{
			ds::StringBuilder sb;
			sb += ds::String("April is the cruellest month, breeding\nLilacs out of the dead land,");
			Assert::IsFalse(sb.IsEmpty());

			const ds::String target1 = "April is the cruellest month, breeding\nLilacs out of the dead land,";
			Assert::AreEqual(target1, sb.ToString());

			sb += ds::String(" mixing\nMemory and desire, stirring\nDull roots with spring rain.");

			const ds::String target2 = "April is the cruellest month, breeding\nLilacs out of the dead land, mixing\nMemory and desire, stirring\nDull roots with spring rain.";
			Assert::AreEqual(target2, sb.ToString());
		}
		TEST_METHOD(AppendingSmallStrings)
		{
			ds::StringBuilder sb;
			sb += ds::String("Ab");
			sb += ds::String("so");
			sb += ds::String("lute ");
			sb += ds::String("Ra");
			sb += ds::String("di");
			sb += ds::String("ance");

			const ds::String target1 = "Absolute Radiance";
			Assert::AreEqual(target1, sb.ToString());
		}
		TEST_METHOD(AppendingCStrings)
		{
			ds::StringBuilder sb;
			sb += "April is the cruellest month, breeding\nLilacs out of the dead land,";
			Assert::IsFalse(sb.IsEmpty());

			const ds::String target1 = "April is the cruellest month, breeding\nLilacs out of the dead land,";
			Assert::AreEqual(target1, sb.ToString());

			sb += " mixing\nMemory and desire, stirring\nDull roots with spring rain.";

			const ds::String target2 = "April is the cruellest month, breeding\nLilacs out of the dead land, mixing\nMemory and desire, stirring\nDull roots with spring rain.";
			Assert::AreEqual(target2, sb.ToString());
		}
		TEST_METHOD(AppendingSingleChar)
		{
			ds::StringBuilder sb;

			const ds::String string1 = "April is the cruellest month, breeding\nLilacs out of the dead land,";
			for (char c : string1) {
				sb += c;
			}

			const ds::String target1 = "April is the cruellest month, breeding\nLilacs out of the dead land,";
			Assert::AreEqual(target1, sb.ToString());

			const ds::String string2 = " mixing\nMemory and desire, stirring\nDull roots with spring rain.";
			for (char c : string2) {
				sb += c;
			}

			const ds::String target2 = "April is the cruellest month, breeding\nLilacs out of the dead land, mixing\nMemory and desire, stirring\nDull roots with spring rain.";
			Assert::AreEqual(target2, sb.ToString());
		}

		TEST_METHOD(AppendingEmptyString)
		{
			ds::StringBuilder sb;
			sb += ds::String("April is the cruellest month, breeding\nLilacs out of the dead land,");
			Assert::IsFalse(sb.IsEmpty());

			const ds::String target1 = "April is the cruellest month, breeding\nLilacs out of the dead land,";
			Assert::AreEqual(target1, sb.ToString());

			sb += ds::String("");

			Assert::AreEqual(target1, sb.ToString());
		}
		TEST_METHOD(AppendingEmptyCString)
		{
			ds::StringBuilder sb;
			sb += "April is the cruellest month, breeding\nLilacs out of the dead land,";
			Assert::IsFalse(sb.IsEmpty());

			const ds::String target1 = "April is the cruellest month, breeding\nLilacs out of the dead land,";
			Assert::AreEqual(target1, sb.ToString());

			sb += "";

			Assert::AreEqual(target1, sb.ToString());
		}
	};

	TEST_CLASS(ToString)
	{
	public:
		TEST_METHOD(StringHasDesiredLength)
		{
			ds::StringBuilder sb;
			sb.Append("Crystal Peak");
			Assert::IsFalse(sb.IsEmpty());

			const ds::String string1 = sb.ToString();
			const ds::String target1 = "Crystal Peak";
			Assert::AreEqual(target1, string1);
			Assert::AreEqual(size_t{ 12 }, string1.Length());

			sb.Append(" Resting Grounds");

			const ds::String string2 = sb.ToString();
			const ds::String target2 = "Crystal Peak Resting Grounds";
			Assert::AreEqual(target2, string2);
			Assert::AreEqual(size_t{ 28 }, string2.Length());
		}
	};

}
