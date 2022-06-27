#pragma once
#include "State.h"

/**
 * @brief State used to to Hybernate or to handle wakeup callbacks.
 */
class HybernateState final : public State
{
public:
	/**
	 * @brief Construct a new Hybernate State object.
	 */
	HybernateState();
	/**
	 * @brief Destroy the Hybernate State object.
	 */
	virtual ~HybernateState();

	/**
	 * @brief Method initializes the Hybernate state.
	 */
	virtual void on_enter() override;
	/**
	 * @brief Method is the update loop of the Hybernate state.
	 */
	virtual void on_stay()  override;
	/**
	 * @brief Method to exit the Hybernate state.
	 */
	virtual void on_exit()  override;

	/**
	 * @brief Callback function called after Hybernation 
	 * needed to return to the statemachine.
	 */
	void on_awake();
};
