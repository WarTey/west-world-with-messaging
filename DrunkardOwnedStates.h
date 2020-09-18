#ifndef DRUNKARD_OWNED_STATES_H
#define DRUNKARD_OWNED_STATES_H

//------------------------------------------------------------------------
//
//  Name:   DrunkardOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Drunkard class.
//          Note that a global state has not been implemented.
//
//------------------------------------------------------------------------

#include "fsm/State.h"

class Drunkard;
struct Telegram;

//------------------------------------------------------------------------
//
//  drunkard changes location to the bar of the saloon and keeps buying
//  Whiskey until he start to fall asleep
//------------------------------------------------------------------------

class ForgetProblemsWithWhiskey : public State<Drunkard>
{
private:

	ForgetProblemsWithWhiskey() {}

	//copy ctor and assignment should be private
	ForgetProblemsWithWhiskey(const ForgetProblemsWithWhiskey&);
	ForgetProblemsWithWhiskey& operator=(const ForgetProblemsWithWhiskey&);

public:

	//this is a singleton
	static ForgetProblemsWithWhiskey* Instance();

	virtual void Enter(Drunkard* drunkard);

	virtual void Execute(Drunkard* drunkard);

	virtual void Exit(Drunkard* drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
//
//  drunkard will fall asleep until his alcohol level is decreased
//  sufficiently
//------------------------------------------------------------------------

class GoFloorToSoberUp : public State<Drunkard>
{
private:

	GoFloorToSoberUp() {}

	//copy ctor and assignment should be private
	GoFloorToSoberUp(const GoFloorToSoberUp&);
	GoFloorToSoberUp& operator=(const GoFloorToSoberUp&);

public:

	//this is a singleton
	static GoFloorToSoberUp* Instance();

	virtual void Enter(Drunkard* drunkard);

	virtual void Execute(Drunkard* drunkard);

	virtual void Exit(Drunkard* drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
//
//  drunkard will go outside with Bob to fight until his alcohol level is
//  too high or until it start to be aggressive
//------------------------------------------------------------------------

class StandUpAndGoOutside : public State<Drunkard>
{
private:

	StandUpAndGoOutside() {}

	//copy ctor and assignment should be private
	StandUpAndGoOutside(const StandUpAndGoOutside&);
	StandUpAndGoOutside& operator=(const StandUpAndGoOutside&);

public:

	//this is a singleton
	static StandUpAndGoOutside* Instance();

	virtual void Enter(Drunkard* drunkard);

	virtual void Execute(Drunkard* drunkard);

	virtual void Exit(Drunkard* drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};

#endif
