#pragma once

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

	bool operator==(const RAI& other) const {
		return positionPtr == other.positionPtr;
	}
	bool operator!=(const RAI& other) const {
		return !operator==(other);
	}
private:
	T* positionPtr;
};
