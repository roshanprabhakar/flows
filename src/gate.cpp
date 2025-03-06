#include "gate.hpp"

#include <stdio.h>

Gate::Gate(uint8_t id): id(id) {
	state = 2;
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

void Gate::updateInput(uint8_t gateId, uint8_t state, uint8_t heads) {
	for (size_t i = 0; i < inputs.size() && heads; ++i) {
		if (inputs[i].first == gateId) {
			inputs[i].second = state;
			heads--;
		}
	}

	while (heads > 0) {
		inputs.push_back({gateId, state});
		--heads;
	}
}

