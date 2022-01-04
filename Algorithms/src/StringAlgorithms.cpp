#include "StringAlgorithms.h"
#include "StackArray.h"
#include "HashSet.h"
#include "Array.h"
#include "Dictionary.h"
#include "Sort.h"
#include "CollectionAlgorithms.h"
#include "MyMath.h"
#include <sstream>

namespace alg {
	namespace string {
		std::string ToString(const ds::Array<char> input) {
			std::stringstream ss;
			for (size_t i = 0; i < input.Size(); i++) {
				ss << input[i];
			}
			return ss.str();
		}

		bool IsUniqueASCII(const std::string& input) {
			const int AsciiSize = 127;

			if (input.size() > AsciiSize) {
				// If the number of characters exceeds the size of the character set,
				// the characters can't possibly be unique
				return false;
			}

			ds::StackArray<bool, AsciiSize> characterExists;
			for (auto& i : characterExists) {
				i = false;
			}

			for (auto& c : input) {
				if (c == ' ') continue; // Ignore spaces

				if (characterExists[c]) {
					// Duplicate found, input not unique
					return false;
				}
				characterExists[c] = true;
			}

			return true;
		}

		bool IsUnique(const std::string& input) {
			ds::HashSet<char> characters;

			for (auto c : input) {
				if (c == ' ') continue; // Ignore spaces

				if (!characters.TryAdd(c)) {
					// Duplicate found, input not unique
					return false;
				}
			}

			return true;
		}

		bool IsPermutation(const std::string& A, const std::string& B) {
			if (A.length() != B.length()) {
				// Can't be a permutation if not the same length
				return false;
			}

			auto arrayA = ds::Array<char>(A);
			auto arrayB = ds::Array<char>(B);

			alg::Quicksort(arrayA);
			alg::Quicksort(arrayB);

			return arrayA == arrayB;
		}

		void URLifySpaces(ds::Array<char>& input) {
			if (input.IsEmpty()) return;

			int i = input.Size() - 1;
			int padding = 0;
			while (i >= 0 && input[i] == ' ') {
				padding++;
				i--;
			}
			
			int stringLength = 0;
			while (i >= 0) {
				if (input[i] == ' ') {
					alg::ShiftElements(input.begin() + i + 1, input.begin() + i + 1 + stringLength, padding);
					padding -= 2;
					input[i+padding] = '%';
					input[i+padding+1] = '2';
					input[i+padding+2] = '0';

					stringLength = 0;
				}
				else {
					stringLength++;
				}
				i--;
			}
		}

		bool IsPermutationOfPalindrome(const ds::String& input) {
			if (!input.IsAlphabetic()) {
				return false;
			}

			const ds::String str = input.ToLower();
			
			ds::Dictionary<char, unsigned int> letterFrequencies;

			for (char c : str) {
				letterFrequencies[c]++;
			}

			// Palindromes have no more than one character that
			// occurs with an odd frequency
			unsigned int numCharsWithOddFrequencies = 0;
			for (auto kv : letterFrequencies) {
				if (kv.key == ' ') continue;

				if (IsOdd(kv.value)) {
					numCharsWithOddFrequencies++;
				}
			}

			return numCharsWithOddFrequencies <= 1;
		}

		bool AreOneEditAway(const ds::String& a, const ds::String& b) {
			size_t lengthDifference = Difference(a.Length(), b.Length());
			if (lengthDifference > 1) return false;

			if (lengthDifference == 0) {
				bool oneEdit = false;
				for (size_t i = 0; i < a.Length(); i++) {
					if (a[i] != b[i]) {
						// Return early if an edit has already been found
						if (oneEdit) {
							return false;
						}
						else {
							oneEdit = true;
						}
					}
				}
				return true;
			}
			else {
				// lengthDifference is 1
				bool oneEdit = false;
				for (size_t ai = 0, bi = 0; ai < a.Length() && bi < b.Length(); ai++, bi++) {
					if (a[ai] != b[bi]) {
						// Return early if an edit has already been found
						if (oneEdit) {
							return false;
						}
						else {
							oneEdit = true;
						}
						// Decrement the smaller string so only the larger
						// string gets incremented next loop
						a.Length() < b.Length() ? ai-- : bi--;
					}
				}
				return true;
			}
		}
	}
}
