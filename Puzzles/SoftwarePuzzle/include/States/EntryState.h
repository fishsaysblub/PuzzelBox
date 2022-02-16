#include "State.h"

class EntryState final : public State
{
public:
	EntryState();
	virtual ~EntryState();

	virtual void on_enter() override;
	virtual void on_exit() override;
};