#pragma once
#include <string>
#include <iostream>
#include <CppUnitTestLogger.h>

namespace Test = Microsoft::VisualStudio::CppUnitTestFramework;


class Tracer {
public:
	Tracer() : Tracer("No Name") {}
	Tracer(std::string name) : name(name), ID(NextID()) {
		std::ostringstream message;
		message << "[+]  " << name << " constructed [" << ID << "]";
		Test::Logger::WriteMessage(message.str().c_str());
	}

	~Tracer() {
		std::ostringstream message;
		message << "[-]  " << name << " destructed [" << ID << "]";
		Test::Logger::WriteMessage(message.str().c_str());
	}

	Tracer(const Tracer& other) {
		name = other.name;
		ID = NextID();

		std::ostringstream message;
		message << "[+=] " << name << " copy constructed [" << other.ID << "] --> [" << ID << "]";
		Test::Logger::WriteMessage(message.str().c_str());
	}

	Tracer& operator= (const Tracer& other) {
		name = other.name;

		std::ostringstream message;
		message << "[=]  " << name << " copy assigned [" << other.ID << "] --> [" << ID << "]";
		Test::Logger::WriteMessage(message.str().c_str());

		return *this;
	}

	Tracer(Tracer&& other) {
		name = other.name;
		ID = NextID();

		other.name += " (Moved From)";

		std::ostringstream message;
		message << "[+>] " << name << " move constructed [" << other.ID << "] --> [" << ID << "]";
		Test::Logger::WriteMessage(message.str().c_str());
	}

	Tracer& operator= (Tracer&& other) {
		name = other.name;

		other.name += " (Moved From)";

		std::ostringstream message;
		message << "[>]  " << name << " move assigned [" << other.ID << "] --> [" << ID << "]";
		Test::Logger::WriteMessage(message.str().c_str());

		return *this;
	}

public:
	std::string name;
	unsigned int ID;

private:
	unsigned int NextID() {
		static unsigned int nextID = 0;
		return nextID++;
	}
};
