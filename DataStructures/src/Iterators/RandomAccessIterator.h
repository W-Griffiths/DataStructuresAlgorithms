#pragma once
#include <cstddef>

template<typename T>
class RandomAccessIterator {
public:
	using RAI = RandomAccessIterator;
	RandomAccessIterator(T* address) : positionPtr(address) { }
	RandomAccessIterator(const RAI& other) : positionPtr(other.positionPtr) { }

	T& operator*() const {
		return *positionPtr;
	}

	RAI& operator++() {
		positionPtr++;
		return *this;
	}
	RAI operator++(int) {
		RAI iter(positionPtr);
		++(*this);
		return iter;
	}
	RAI& operator--() {
		positionPtr--;
		return *this;
	}
	RAI operator--(int) {
		RAI iter(positionPtr);
		--(*this);
		return iter;
	}

	RAI operator+(size_t length) const {
		return RAI(positionPtr + length);
	}
	RAI operator-(size_t length) const {
		return RAI(positionPtr - length);
	}

	ptrdiff_t operator-(const RAI& other) const {
		return positionPtr - other.positionPtr;
	}

	T& operator[](ptrdiff_t n){
		return *(positionPtr + n);
	}

	bool operator==(const RAI& other) const {
		return positionPtr == other.positionPtr;
	}
	bool operator!=(const RAI& other) const {
		return !operator==(other);
	}
	bool operator>(const RAI& other) const {
		return positionPtr > other.positionPtr;
	}
	bool operator<(const RAI& other) const {
		return positionPtr < other.positionPtr;
	}
	bool operator>=(const RAI& other) const {
		return positionPtr >= other.positionPtr;
	}
	bool operator<=(const RAI& other) const {
		return positionPtr <= other.positionPtr;
	}
private:
	T* positionPtr;
};
