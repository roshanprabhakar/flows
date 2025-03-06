#ifndef GATE_HPP
#define GATE_HPP

#include <queue>
#include <vector>
#include <stdint.h>

#define DUMMY_GATE_ID (uint8_t)-1

class Module;

class Gate {

protected:
	uint8_t id;
	uint8_t state;

	// All outbound connections of this gate.
	// These are gates that receive this gate's output as input
	std::vector<Gate *> connections;

	// For each element in connections, how many input heads
	// does this gate consume.
	std::vector<int> numConnectedHeads;

	// Track the two inbound connections. Even indices i
	// indicate wire addresses, and i+1 indicates the wire's
	// value as of the last read.
	std::vector<std::pair<uint8_t, uint8_t>> inputs;

public:
	Gate(uint8_t);
	virtual ~Gate() = default;

	virtual uint8_t computeState(void) = 0;

	virtual void updateInput(uint8_t, uint8_t, uint8_t);
	static void updateState(std::queue<Gate *>&);
	
	// Make Module a friend class so it can access connections and state
	friend class Module;
};

#endif // GATE_HPP
