#include <stdint.h>

#include <vector>
#include <utility>

#include "../module.hpp"
#include "../stdcomponent.hpp"

// All the input gates into the D Flip-Flop module.
static const std::vector<std::pair<int, uint8_t>> inputs = {
	{0,0}, // Gate 0 (rstn) - initially 0
	{1,0}, // Gate 1 (d) - initially 0
	{2,1}  // Gate 2 - initially 1
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
// This component describes a D-Flip Flop. Notice what states are 
// generated as we randomly populate the sequence vector--The clock
// signal is essentially an enable, with reset and data functioning
// as expected. When reset is 1, and enable(clock) is 1, the output
// is set to the data signal. When reset 1 and enable(clock) is 0, 
// the output maintains the last value it was set to. When reset is
// activated (reset=0), and the enable bit is on, the output is set 
// to 0.
//
Module *StandardComponent::DFF(void) {
	Module *m = new Module(numGates, connections, inputs, outputGateRange, inputGateRange);
	return m;
}



