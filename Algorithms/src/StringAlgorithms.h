#pragma once
#include "Array.h"
#include <string>

namespace alg {
	namespace string {
		bool IsUniqueASCII(const std::string&);
		bool IsUnique(const std::string&);
		bool IsPermutation(const std::string&, const std::string&);
		void URLifySpaces(ds::Array<char>&);
	}
}
