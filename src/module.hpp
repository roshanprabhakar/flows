#ifndef MODULE_HPP
#define MODULE_HPP

#include "gate-types.hpp"
#include <vector>
#include <queue>
#include <utility>

// 
// To keep things easy, input gates are contigously layed out at the start
// of the gates array, and output gates are contiguously positioned at the
// end of the gates array.
//

class Module {
private:
	std::vector<Gate *> gates;
	uint8_t outGateRange; 
	uint8_t inGateRange;
	uint8_t numGates;
    
public:
	// Constructor that sets up the network of gates based on connections
	Module(uint8_t gateCount, 
				 const std::vector<std::pair<int, std::pair<int, int>>>& connections,
				 const std::vector<std::pair<int, uint8_t>>& inputs,
				 uint8_t outGateRange,
				 uint8_t inputGateRange);
	~Module(void);
	
	// Propagate changes through the network
	void propagate();

	Gate *getGate(int);

	// Get the state of a specific gate
	uint8_t getGateState(int gateId);
	
	// Debug helper to print gate states
	void dumpModule(int *);
};

#endif // MODULE_HPP
