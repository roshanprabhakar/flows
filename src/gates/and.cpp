#include "../gate-types.hpp"

And::And(uint8_t id): Gate(id) { }

uint8_t And::computeState() {

	// If we have no inputs, the output is undefined.
	if (inputs.size() == 0) { return 2; }
	
	// If any input to the AND is undefiend, the output is undefined.
	for (const auto &pair : inputs) {
		if (pair.second & 2) { return 2; }
	}

	// Otherwise, return the and of the inputs.
	uint8_t out = inputs[0].second;
	for (const auto &pair : inputs) {
		out &= pair.second;
	}
	return out & 1;
}

