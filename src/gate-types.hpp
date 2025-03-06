#include "gate.hpp"

class Nand : public Gate {
public:
	Nand(uint8_t);
	uint8_t computeState(void) override;
};

class Xor : public Gate {
public:
	Xor(uint8_t);
	uint8_t computeState(void) override;
};

class And : public Gate {
	And(uint8_t);
	uint8_t computeState(void) override;
};
