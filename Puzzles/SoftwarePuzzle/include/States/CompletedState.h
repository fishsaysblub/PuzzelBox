#pragma once
#include "State.h"

class CompletedState final : public State
{
public:
	CompletedState();
	virtual ~CompletedState();

	virtual void on_enter() override;
	virtual void on_stay()  override;
	virtual void on_exit()  override;
};