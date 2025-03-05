#ifndef MODULE_HPP
#define MODULE_HPP

#include "gate.hpp"
#include <vector>
#include <queue>
#include <utility>

class Module {
private:
	std::vector<Gate> gates;
	uint8_t outGate; 
	uint8_t inGateRange;
    
public:
	// Constructor that sets up the network of gates based on connections
	Module(uint8_t gateCount, 
				 const std::vector<std::pair<int, std::pair<int, int>>>& connections,
				 const std::vector<std::pair<int, uint8_t>>& inputs,
				 uint8_t outGate,
				 uint8_t inputGateRange);
	
	// Propagate changes through the network
	void propagate();

	Gate *getGate(int);

	// Get the state of a specific gate
	uint8_t getGateState(int gateId);
	
	// Debug helper to print gate states
	void dumpModule(int *);
};

#endif // MODULE_HPP
