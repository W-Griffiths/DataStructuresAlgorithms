#pragma once
#include "Array.h"
#include <string>

namespace util {

	//----- Declarations
	template<typename T>
	void Swap(T& A, T& B);

	std::string ToString(const ds::Array<char>);
	//-----

	template<typename T>
	void Swap(T& A, T& B) {
		T temp = A;
		A = B;
		B = temp;
	}

}
