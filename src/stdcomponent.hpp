#include "module.hpp"

class StandardComponent {
	StandardComponent() = delete;
public:
	static Module *DFF(void);
	static Module *BitAdder(void);
	// Add more components as we go.
};
