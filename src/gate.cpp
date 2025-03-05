#include "gate.hpp"

#include <stdio.h>

Gate::Gate(uint8_t id): id(id) {
	inputs[0] = inputs[2] = (uint8_t)-1;
	inputs[1] = inputs[3] = (uint8_t)3;
	state = 2;
}

uint8_t Gate::computeState() {
	uint8_t a = inputs[1], b = inputs[3];

	// If either input to the NAND is 0, the output is 1.
	if (!a || !b) { return 1; }

	// If neither inputs are 0, and one is undefined, the output
	// is undefined.
	else if ((a & 2) || (b & 2)) { return 2; }
	
	// In this case both are 1, so state is 0.
	else { return 0; }
}

void Gate::updateInput(uint8_t gateId, uint8_t state, uint8_t heads) {
	// printf("Gate %u receiving input from gate %u with state %u and %u heads\n", id, gateId, state, heads);
	
	if (heads == 1) {
		// gateId is only connected to one of the inputs of this gate.

		uint8_t bin = 
			(inputs[0] == (uint8_t)-1) ? 0 : 
			(inputs[2] == (uint8_t)-1) ? 2 : (uint8_t)-1;

		if (bin != (uint8_t)-1) { inputs[bin] = gateId; }

		uint8_t idx = gateId == inputs[0] ? 1 : 3;
		inputs[idx] = state;
	} else if (heads == 2) {
		// gateId is connected to both input heads of this gate.
			
		inputs[0] = inputs[2] = gateId;
		inputs[1] = inputs[3] = state;
	}
}

void Gate::updateState(std::queue<Gate *> &toUpdate) {
	while (toUpdate.size() != 0) {

		Gate *currentGate = toUpdate.front();

		uint8_t oldState = currentGate->state;
		uint8_t newState = currentGate->computeState();

		currentGate->state = newState;

		if (oldState != newState) {

			for (size_t i = 0; i < currentGate->connections.size(); ++i) {
				Gate *neighbor = currentGate->connections[i];
				int numHeads = currentGate->numConnectedHeads[i];

				neighbor->updateInput(currentGate->id, newState, numHeads);
				toUpdate.push(neighbor);
			}
		}

		toUpdate.pop();
	}
}

