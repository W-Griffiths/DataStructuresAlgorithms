#include "CppUnitTest.h"
#include "StringAlgorithms.h"
#include "Array.h"
#include "Utilities.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace String {

	TEST_CLASS(UniqueASCII)
	{
	public:

		TEST_METHOD(UniqueStringsPass)
		{
			std::string fruit = "Pear";
			Assert::IsTrue(alg::string::IsUniqueASCII(fruit));

			fruit = "Apricot";
			Assert::IsTrue(alg::string::IsUniqueASCII(fruit));

			fruit = "qwertyuiop[]asdfghjkl;'zxcvbnm,./";
			Assert::IsTrue(alg::string::IsUniqueASCII(fruit));
		}
		TEST_METHOD(NonUniqueStringsFail)
		{
			std::string fruit = "Cherry";
			Assert::IsFalse(alg::string::IsUniqueASCII(fruit));

			fruit = "Banana";
			Assert::IsFalse(alg::string::IsUniqueASCII(fruit));
		}
		TEST_METHOD(CaseSensitive)
		{
			std::string fruit = "Pumpkin";
			Assert::IsTrue(alg::string::IsUniqueASCII(fruit));

			fruit = "pumpkin";
			Assert::IsFalse(alg::string::IsUniqueASCII(fruit));
		}
		TEST_METHOD(IgnoreSpaces)
		{
			std::string fruits = "Lemon & Fig";
			Assert::IsTrue(alg::string::IsUniqueASCII(fruits));
		}
	};

	TEST_CLASS(Unique)
	{
	public:

		TEST_METHOD(UniqueStringsPass)
		{
			std::string fruit = "Pear";
			Assert::IsTrue(alg::string::IsUnique(fruit));

			fruit = "Apricot";
			Assert::IsTrue(alg::string::IsUnique(fruit));

			fruit = "qwertyuiop[]asdfghjkl;'zxcvbnm,./";
			Assert::IsTrue(alg::string::IsUnique(fruit));
		}
		TEST_METHOD(NonUniqueStringsFail)
		{
			std::string fruit = "Cherry";
			Assert::IsFalse(alg::string::IsUnique(fruit));

			fruit = "Banana";
			Assert::IsFalse(alg::string::IsUnique(fruit));
		}
		TEST_METHOD(CaseSensitive)
		{
			std::string fruit = "Pumpkin";
			Assert::IsTrue(alg::string::IsUnique(fruit));

			fruit = "pumpkin";
			Assert::IsFalse(alg::string::IsUnique(fruit));
		}
		TEST_METHOD(IgnoreSpaces)
		{
			std::string fruits = "Lemon & Fig";
			Assert::IsTrue(alg::string::IsUnique(fruits));
		}
	};

	TEST_CLASS(Permutation)
	{
	public:

		TEST_METHOD(IdenticalStringsPass)
		{
			std::string fruit1 = "Apricot";
			std::string fruit2 = "Apricot";
			Assert::IsTrue(alg::string::IsPermutation(fruit1, fruit2));
		}
		TEST_METHOD(PermutationsPass)
		{
			std::string dog1 = "labrador";
			std::string dog2 = "rablardo";
			std::string dog3 = "lodrarba";
			Assert::IsTrue(alg::string::IsPermutation(dog1, dog2));
			Assert::IsTrue(alg::string::IsPermutation(dog1, dog3));
		}
		TEST_METHOD(NonPermutationsFail)
		{
			std::string fruit = "Banana";
			std::string fruit2 = "Bananana";
			std::string fruit3 = "Bonobo";
			Assert::IsFalse(alg::string::IsPermutation(fruit, fruit2));
			Assert::IsFalse(alg::string::IsPermutation(fruit, fruit3));
		}
		TEST_METHOD(CaseSensitive)
		{
			std::string dog1 = "Labrador";
			std::string dog2 = "labrador";
			std::string dog3 = "rablador";
			std::string dog4 = "rabLador";
			Assert::IsFalse(alg::string::IsPermutation(dog1, dog2));
			Assert::IsFalse(alg::string::IsPermutation(dog1, dog3));
			Assert::IsTrue(alg::string::IsPermutation(dog1, dog4));
		}
		TEST_METHOD(WithSpaces)
		{
			std::string wings = "Red Bull Racing";
			std::string wings2 = "Bull Red Racing";
			std::string wings3 = "Red BullRacing";
			Assert::IsTrue(alg::string::IsPermutation(wings, wings2));
			Assert::IsFalse(alg::string::IsPermutation(wings, wings3));
		}
	};

	TEST_CLASS(URLifySpaces)
	{
	public:

		TEST_METHOD(ValidInputPasses)
		{
			ds::Array<char> path ("www.website.com/some page with spaces      ");
			ds::Array<char> expectedPath ("www.website.com/some%20page%20with%20spaces");

			alg::string::URLifySpaces(path);

			Assert::AreEqual(util::ToString(expectedPath), util::ToString(path));
		}

		TEST_METHOD(InputWithNoSpacesIsUnmodified)
		{
			ds::Array<char> input("thisstringhasnospaces");
			ds::Array<char> expectedOutput("thisstringhasnospaces");

			alg::string::URLifySpaces(input);

			Assert::AreEqual(util::ToString(expectedOutput), util::ToString(input));
		}

		TEST_METHOD(LeadingSpacesAlsoConvert)
		{
			ds::Array<char> input(" a string with leading spaces          ");
			ds::Array<char> expectedOutput("%20a%20string%20with%20leading%20spaces");

			alg::string::URLifySpaces(input);

			Assert::AreEqual(util::ToString(expectedOutput), util::ToString(input));
		}

		TEST_METHOD(AllSpacesIsIgnored)
		{
			ds::Array<char> input("   ");
			ds::Array<char> expectedOutput("   ");

			alg::string::URLifySpaces(input);

			Assert::AreEqual(util::ToString(expectedOutput), util::ToString(input));
		}
	};
}
