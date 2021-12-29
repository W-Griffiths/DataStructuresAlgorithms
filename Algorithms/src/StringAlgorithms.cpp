#include "StringAlgorithms.h"
#include "StackArray.h"
#include "HashSet.h"
#include "Array.h"
#include "Sort.h"
#include "Utilities.h"

namespace alg {
	namespace string {
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

		/// <summary>
		/// Modifies a char array in place to replace spaces with
		/// the %20 URL symbol.
		/// This algorithm assumes the input has enough trailing
		/// spaces to perform the operation correctly.
		/// </summary>
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
					util::ShiftElements(input.begin() + i + 1, input.begin() + i + 1 + stringLength, padding);
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
	}
}
