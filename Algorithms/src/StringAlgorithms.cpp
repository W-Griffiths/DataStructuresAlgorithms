#include "StringAlgorithms.h"
#include "Array.h"

namespace alg {
	namespace string {
		bool IsUniqueASCII(const std::string& input) {
			const int AsciiSize = 127;

			if (input.size() > AsciiSize) {
				// If the number of characters exceeds the size of the character set,
				// the characters can't possibly be unique
				return false;
			}

			ds::Array<bool, AsciiSize> characterExists;
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
	}
}
