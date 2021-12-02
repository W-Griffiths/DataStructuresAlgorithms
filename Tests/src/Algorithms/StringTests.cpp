#include "CppUnitTest.h"
#include "StringAlgorithms.h"
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

}
