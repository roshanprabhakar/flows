#include <stdint.h>

#include <vector>
#include <utility>

#include "../module.hpp"
#include "../stdcomponent.hpp"

// All the input gates into the 2-bit adder
static const std::vector<std::pair<int, uint8_t>> inputs = {
	{0,0}, // Gate 0, the carry-in bit.
	{1,0}, // Gate 1, the first operand bit.
	{2,0}, // Gate 2, the second operand bit.
};

// The connections between gates within the D Flip-Flop.
static const std::vector<std::pair<int, std::pair<int, int>>> connections = {
	{3, {0,1}},  // Gate 3 gets inputs from gates 0 and 1
	{4, {3,3}},  // Gate 4 gets both inputs from gate 3
	{5, {2,3}},  // Gate 5 gets inputs from gates 2 and 3
	{6, {2,4}},  // Gate 6 gets inputs from gates 2 and 4
	{7, {5,8}},  // Gate 7 gets inputs from gates 5 and 8
	{8, {6,7}}   // Gate 8 gets inputs from gates 6 and 7
};

// More module parameters;
static const uint8_t numGates = 9;
static const uint8_t inputGateRange = 3; // First 3 gates are input.
static const uint8_t outputGateRange = 1; // Last gate is output.

// 
// TODO
//
Module *StandardComponent::BitAdder(void) {
	Module *m = new Module(numGates, connections, inputs, outputGateRange, inputGateRange);
	return m;
}



