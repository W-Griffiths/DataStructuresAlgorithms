#pragma once
#include "Array.h"
#include "MyString.h"
#include <string>

namespace alg {
	namespace string {
		std::string ToString(const ds::Array<char>);

		bool IsUniqueASCII(const std::string&);
		bool IsUnique(const std::string&);
		bool IsPermutation(const std::string&, const std::string&);
		/// <summary>
		/// Modifies a char array in place to replace spaces with
		/// the %20 URL symbol.
		/// This algorithm assumes the input has enough trailing
		/// spaces to perform the operation correctly.
		/// </summary>
		void URLifySpaces(ds::Array<char>&);
		bool IsPermutationOfPalindrome(const ds::String&);
		bool AreOneEditAway(const ds::String&, const ds::String&);
	}
}
