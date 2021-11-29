#pragma once
#include <CppUnitTestLogger.h>

namespace Test = Microsoft::VisualStudio::CppUnitTestFramework;

class ReferenceCounter {
public:
	ReferenceCounter(int* ptr) : countPtr(ptr) {
		(*countPtr)++;

		std::ostringstream message;
		message << "[Constructor] Count = " << *countPtr;
		Test::Logger::WriteMessage(message.str().c_str());
	}
	~ReferenceCounter() {
		if (!countPtr) {
			return;
		}
			
		(*countPtr)--;

		std::ostringstream message;
		message << "[Destructor] Count = " << *countPtr;
		Test::Logger::WriteMessage(message.str().c_str());
	}

	ReferenceCounter(ReferenceCounter& other) {
		this->countPtr = other.countPtr;
		other.countPtr = nullptr;
	}
	ReferenceCounter(ReferenceCounter&& other) noexcept {
		this->countPtr = other.countPtr;
		other.countPtr = nullptr;
	}

	ReferenceCounter& operator= (ReferenceCounter& other) {
		this->countPtr = other.countPtr;
		other.countPtr = nullptr;
		return *this;
	}
	ReferenceCounter& operator= (ReferenceCounter&& other) noexcept {
		this->countPtr = other.countPtr;
		other.countPtr = nullptr;
		return *this;
	}

private:
	int* countPtr;
};
