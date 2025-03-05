#ifndef GATE_HPP
#define GATE_HPP

#include <queue>
#include <vector>
#include <stdint.h>

class Module; // Forward declaration

class Gate {
	uint8_t id;
	uint8_t state;

	// All outbound connections of this gate.
	// These are gates that receive this gate's output as input
	std::vector<Gate *> connections;

	// For each element in connections, how many input heads
	// does this gate consume.
	std::vector<int> numConnectedHeads;

public:

	// Track the two inbound connections. Even indices i
	// indicate wire addresses, and i+1 indicates the wire's
	// value as of the last read.
	uint8_t inputs[4];

	Gate(uint8_t);

	uint8_t computeState(void);
	void updateInput(uint8_t, uint8_t, uint8_t);
	static void updateState(std::queue<Gate *>&);
	
	// Make Module a friend class so it can access connections and state
	friend class Module;
};

#endif // GATE_HPP
