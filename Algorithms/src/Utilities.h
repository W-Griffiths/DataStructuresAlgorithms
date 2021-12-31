#pragma once

namespace util {

	//----- Declarations
	template<typename T>
	void Swap(T& A, T& B);
	//-----

	template<typename T>
	void Swap(T& A, T& B) {
		T temp = A;
		A = B;
		B = temp;
	}

}
