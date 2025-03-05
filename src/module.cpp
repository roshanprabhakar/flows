#include "module.hpp"
#include <stdio.h>

Module::Module(uint8_t gateCount, 
               const std::vector<std::pair<int, std::pair<int, int>>>& connections,
               const std::vector<std::pair<int, uint8_t>>& inputs,
							 uint8_t outputGate,
							 uint8_t inputGateRange)
	:outGate(outputGate), inGateRange(inputGateRange) {
    
	// Initialize all gates
	gates.reserve(gateCount);
	for (uint8_t i = 0; i < gateCount; i++) {
		gates.emplace_back(i);
	}
    
	// Set up connections between gates
	for (const auto& conn : connections) {
		int toGate = conn.first;
		int fromGate1 = conn.second.first;
		int fromGate2 = conn.second.second;

		gates[fromGate1].connections.push_back(&gates[toGate]);
		if (fromGate1 == fromGate2) {
			gates[fromGate1].numConnectedHeads.push_back(2);
			gates[toGate].updateInput(fromGate1, gates[fromGate1].state, 2);
		} else {
			gates[fromGate1].numConnectedHeads.push_back(1);
			gates[toGate].updateInput(fromGate1, gates[fromGate1].state, 1);

			gates[fromGate2].connections.push_back(&gates[toGate]);
			gates[fromGate2].numConnectedHeads.push_back(1);
			gates[toGate].updateInput(fromGate2, gates[fromGate2].state, 1);
		}
	}

	for (const auto& input : inputs) {
		int gateId = input.first;
		uint8_t value = input.second;

		if (gateId >= 0 && gateId < gateCount) {

			if (value == 0) {
				gates[gateId].inputs[1] = gates[gateId].inputs[3] = 1;
			} else if (value == 1) {
				gates[gateId].inputs[1] = 0;
			} else {
				gates[gateId].inputs[1] = gates[gateId].inputs[3] = 2;
			}
		}
	}
}

void Module::propagate() {
	std::queue<Gate*> toUpdate;

	// Start with gates that have received input
	for (auto& gate : gates) {
		if (gate.computeState() != gate.state) {
			toUpdate.push(&gate);
		}
	}

	// If no gates need updating, push all gates to ensure initial propagation
	if (toUpdate.empty()) {
		for (auto& gate : gates) {
			toUpdate.push(&gate);
		}
	}
	
	// Use the static method to update all gates
	Gate::updateState(toUpdate);
}

Gate *Module::getGate(int gate) {
	return &gates[gate];
}

uint8_t Module::getGateState(int gateId) {
	if (gateId >= 0 && gateId < static_cast<int>(gates.size())) {
		return gates[gateId].computeState();
	}
	return 0;
}

void Module::dumpModule(int *output) {
	if (output == NULL) {
		printf("[Data] { ");
	}
	for (size_t i = 0; i < gates.size(); ++i) {
		if (output != NULL) { output[i] = gates[i].computeState(); }
		else {
			if (i == outGate) { printf(" [ouput] "); }
			if (i == inGateRange) { printf("} "); }
			printf("%d ", gates[i].computeState());
		}
	}
	if (output == NULL) {
		printf("\n");
	}
}
