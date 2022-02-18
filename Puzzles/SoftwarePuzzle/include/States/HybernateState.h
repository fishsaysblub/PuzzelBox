#pragma once
#include <utility>
#include "State.h"

class HybernateState final : public State
{
public:
	HybernateState();
	virtual ~HybernateState();

	virtual void on_enter() override;
	virtual void on_exit() override;

	void hybernate();
	void on_awake();
};
