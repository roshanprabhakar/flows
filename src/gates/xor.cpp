#include "../gate-types.hpp"

Xor::Xor(uint8_t id): Gate(id) { }

uint8_t Xor::computeState() {

	// Xor output is undefined if there isn't at least 2 outputs, this is
	// equivalent to 2 undefiend inputs.
	if (inputs.size() < 2) { return 2; }
	
	// If any input in the NAND is undefined, the output is undefined.
	for (const auto &pair : inputs) {
		if (pair.second & 2) { return 2; }
	}

	// In this case we have at least 2 defined inputs, return the xor of
	// all of them.
	uint8_t out = inputs[0].second;
	for (const auto &pair : inputs) {
		out ^= pair.second;
	}
	return out & 1;
}

