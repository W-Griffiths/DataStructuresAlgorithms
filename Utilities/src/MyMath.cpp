#include "MyMath.h"

size_t Min(const size_t a, const size_t b) {
	if (b < a) {
		return b;
	}
	else {
		// Returns a if equal
		return a;
	}
}
int Min(const int a, const int b) {
	if (b < a) {
		return b;
	}
	else {
		// Returns a if equal
		return a;
	}
}

size_t Max(const size_t a, const size_t b) {
	if (b > a) {
		return b;
	}
	else {
		// Returns a if equal
		return a;
	}
}

int Max(const int a, const int b) {
	if (b > a) {
		return b;
	}
	else {
		// Returns a if equal
		return a;
	}
}
