#ifndef DRUNKARD_H
#define DRUNKARD_H

//------------------------------------------------------------------------
//
//  Name:   Drunkard.h
//
//  Desc:   A class defining a drunkard.
//
//------------------------------------------------------------------------

#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "DrunkardOwnedStates.h"
#include "fsm/StateMachine.h"

template <class entity_type> class State;
struct Telegram;

//above this value a drunkard start to fall asleep
const int AlcoholLevel = 5;

//the amount of anger a drunkard can accumulate before becoming aggressive
const int AngerLevel = 2;

class Drunkard : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Drunkard>* m_pStateMachine;

	location_type m_Location;

	//the higher the value, the more drunk the drunkard
	int m_iDrunk;

public:

	Drunkard(int id) :m_Location(saloon), m_iDrunk(0), BaseGameEntity(id)
	{
		//set up state machine
		m_pStateMachine = new StateMachine<Drunkard>(this);

		m_pStateMachine->SetCurrentState(ForgetProblemsWithWhiskey::Instance());

		/* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE DRUNKARD */
	}

	~Drunkard() { delete m_pStateMachine; }

	//this must be implemented
	void Update();

	//so must this
	virtual bool HandleMessage(const Telegram& msg);

	StateMachine<Drunkard>* GetFSM() const { return m_pStateMachine; }

	//-------------------------------------------------------------accessors
	location_type Location() const { return m_Location; }
	void ChangeLocation(location_type loc) { m_Location = loc; }

	bool Drunk() const;
	bool Rested() const;
	void ResetDrunk() { m_iDrunk = 0; };
	void IncreaseDrunk() { m_iDrunk += 1; }
};

#endif
