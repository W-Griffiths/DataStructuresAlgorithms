#pragma once
#include <random>

namespace util {

	class Random {
	public:
		/// <summary>
		/// Produces values from min to max, inclusive.
		/// Seeds using the current high-resolution time.
		/// </summary>
		Random(size_t min, size_t max);
		Random(size_t min, size_t max, size_t seed);
		size_t Next();

	private:
		std::uniform_int_distribution<size_t> distribution;
		std::default_random_engine generator;
	};

}
