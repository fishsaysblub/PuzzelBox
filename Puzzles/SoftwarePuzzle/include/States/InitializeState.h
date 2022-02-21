#pragma once
#include "State.h"

class InitializeState final : public State
{
public:
	InitializeState();
	virtual ~InitializeState();

	virtual void on_enter() override;
	virtual void on_stay()  override;
	virtual void on_exit()  override;
};