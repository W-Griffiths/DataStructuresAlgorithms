#include "Random.h"
#include <chrono>

namespace alg {

	Random::Random(size_t min, size_t max) :	distribution(min, max),
												generator(static_cast<size_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count())) {}
	Random::Random(size_t min, size_t max, size_t seed) : distribution(min, max), generator(seed) {}

	size_t Random::Next() {
		return distribution(generator);
	}

}
