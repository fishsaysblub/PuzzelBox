#include "State.h"

class InitializeState final : public State
{
public:
	InitializeState();
	virtual ~InitializeState();

	virtual void on_enter() override;
			void on_stay();
	virtual void on_exit() override;
};