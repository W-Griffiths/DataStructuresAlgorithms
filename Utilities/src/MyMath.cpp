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

size_t Difference(const size_t a, const size_t b) {
	return a > b ? a - b : b - a;
}

bool IsEven(int num) {
	return num % 2 == 0;
}

bool IsOdd(int num) {
	return num % 2 == 1;
}

bool IsEven(unsigned int num) {
	return num % 2 == 0;
}

bool IsOdd(unsigned int num) {
	return num % 2 == 1;
}
