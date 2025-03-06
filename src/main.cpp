#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <ctime>

#include "stdcomponent.hpp"

// Function to generate a random bit (0 or 1)
int generateRandomBit() {
    static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> dist(0, 1);
    return dist(rng);
}

void executeSequence(std::vector<std::vector<int>> sequences, Module *m) {
#define SET_IN(m, i, v) (m)->getGate(i)->updateInput(DUMMY_GATE_ID,((v)==1?0:1),2);
	
	for (const auto &inputs : sequences) {
		for (int i = 0; i < inputs.size(); ++i) {
			SET_IN(m, i, inputs[i]);
		}
		m->propagate();
		m->dumpModule(NULL);
	}
}

int main(int argc, char const **argv) {
	Module *m = StandardComponent::DFF();

	// Initialize and show initial state
	std::cout << "\n=== INITIAL STATE ===" << std::endl;
	m->dumpModule(NULL);
	m->propagate();
	std::cout << "\n=== AFTER INITIAL PROPAGATION ===" << std::endl;
	m->dumpModule(NULL);
	std::cout << "\n\n";

	std::vector<std::vector<int>> sequence;
	for (int i = 0; i < 50; ++i) {
		sequence.push_back({i%3!=0, generateRandomBit(), (i/5)&1});
	}

	executeSequence(sequence, m);
	delete m;
}
