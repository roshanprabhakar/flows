#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <ctime>

#include "module.hpp"

// Function to generate a random bit (0 or 1)
int generateRandomBit() {
    static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> dist(0, 1);
    return dist(rng);
}

void executeSequence(std::vector<std::vector<int>> sequences, Module &m) {
#define SET_IN(m, i, v) (m).getGate(i)->updateInput(50,((v)==1?0:1),2);
	
	for (const auto &inputs : sequences) {
		for (int i = 0; i < inputs.size(); ++i) {
			SET_IN(m, i, inputs[i]);
		}
		m.propagate();
		m.dumpModule(NULL);
	}
}

void newComponent() {

}

void dff() {
    
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

	// Create the module with the same structure as before
	std::vector<std::pair<int, uint8_t>> inputs = {
		{0,0}, // Gate 0 (rstn) - initially 0
		{1,0}, // Gate 1 (d) - initially 0
		{2,1}  // Gate 2 - initially 1
	};

	std::vector<std::pair<int, std::pair<int, int>>> connections = {
		{3, {0,1}},  // Gate 3 gets inputs from gates 0 and 1
		{4, {3,3}},  // Gate 4 gets both inputs from gate 3
		{5, {2,3}},  // Gate 5 gets inputs from gates 2 and 3
		{6, {2,4}},  // Gate 6 gets inputs from gates 2 and 4
		{7, {5,8}},  // Gate 7 gets inputs from gates 5 and 8
		{8, {6,7}}   // Gate 8 gets inputs from gates 6 and 7
	};
	
	Module m(9, connections, inputs, 8, 3);
	
	// Initialize and show initial state
	std::cout << "\n=== INITIAL STATE ===" << std::endl;
	m.dumpModule(NULL);
	m.propagate();
	std::cout << "\n=== AFTER INITIAL PROPAGATION ===" << std::endl;
	m.dumpModule(NULL);
	std::cout << "\n\n";

	std::vector<std::vector<int>> sequence;
	for (int i = 0; i < 50; ++i) {
		sequence.push_back({i%3!=0, generateRandomBit(), (i/5)&1});

	}
#if 0
	std::vector<std::vector<int>> sequence = {
		{1,0,0},
		{1,1,0},
		{1,0,0},
		{1,0,0},
		{1,1,1},
		{1,0,1},
		{1,1,1},
		{1,1,1},
		{1,0,0},
		{1,1,0},
		{1,1,0},
		{1,1,0},
		{1,0,0},
		{1,0,1},
		{1,0,1},
		{1,1,1}
	};
#endif

	executeSequence(sequence, m);
}

int main(int argc, char const **argv) {
	dff();
}
