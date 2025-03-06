#include "../gate-types.hpp"

Nand::Nand(uint8_t id): Gate(id) { }

uint8_t Nand::computeState() {
	
	// If any input to the NAND is 0, the output is 1.
	for (const auto &pair : inputs) {
		if (pair.second == 0) { return 1; }
	}

	// If neither inputs are 0, and one is undefined, the output
	// is undefined.
	for (const auto &pair : inputs) {
		if (pair.second & 2) { return 2; }
	}

	// In this all cases are 1, so state is 0.
	return 0;
}

