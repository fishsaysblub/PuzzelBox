#pragma once

typedef enum
{
	INITIALIZE,
	HYBERNATE,
	ENTRY,
	RUNNING,
	COMPLETED
} EState;

// Abstract class
// Dit betekenet deze class doet niks maar zorgt er voor dat over geerft kan worden

class State
{
public:
	virtual void on_enter() = 0;
	virtual void on_exit() = 0;
};