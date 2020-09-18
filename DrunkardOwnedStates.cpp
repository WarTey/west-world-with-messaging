#include "DrunkardOwnedStates.h"
#include "fsm/State.h"
#include "Drunkard.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//------------------------------------------------------------------------ForgetProblemsWithWhiskey

ForgetProblemsWithWhiskey* ForgetProblemsWithWhiskey::Instance()
{
	static ForgetProblemsWithWhiskey instance;

	return &instance;
}

void ForgetProblemsWithWhiskey::Enter(Drunkard* pDrunkard)
{
	if (pDrunkard->Location() != saloon)
	{
		pDrunkard->ChangeLocation(saloon);

		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Boy, ah sure is thusty! Walking to the bar of the saloon";
	}
}

void ForgetProblemsWithWhiskey::Execute(Drunkard* pDrunkard)
{
	pDrunkard->IncreaseDrunk();

	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "That's mighty fine sippin' Whiskey";

	if (!pDrunkard->Rested()) cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Hiiips!";

	if (pDrunkard->Drunk()) pDrunkard->GetFSM()->ChangeState(GoFloorToSoberUp::Instance());
}

void ForgetProblemsWithWhiskey::Exit(Drunkard* pDrunkard)
{
	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Leaving the bar of the saloon";

	if (pDrunkard->Drunk()) cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Ohhhh boy! I'm too much drunk!";
}

bool ForgetProblemsWithWhiskey::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_HiEveryone:

		cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID()) << " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": Lookin' at Bob";

		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pDrunkard->ID(), ent_Miner_Bob, Msg_SilenceYoungMadman, NO_ADDITIONAL_INFO);

		return true;

	case Msg_CalmDown:

		cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID()) << " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		pDrunkard->GetFSM()->ChangeState(StandUpAndGoOutside::Instance());

		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pDrunkard->ID(), ent_Miner_Bob, Msg_HorribleHeadache, NO_ADDITIONAL_INFO);

		return true;
	}//end switch

	return false; //send message to global message handler
}

//------------------------------------------------------------------------GoFloorToSoberUp

GoFloorToSoberUp* GoFloorToSoberUp::Instance()
{
	static GoFloorToSoberUp instance;

	return &instance;
}

void GoFloorToSoberUp::Enter(Drunkard* pDrunkard)
{
	if (pDrunkard->Location() != ground)
	{
		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Let's try to stand up and... ZZZZ...";

		pDrunkard->ChangeLocation(ground);
	}
}

void GoFloorToSoberUp::Execute(Drunkard* pDrunkard)
{
	//if drunkard is not drunk start to drink again.
	if (pDrunkard->Rested())
	{
		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "All mah alcohol level has drained away. Time to drink again!";

		pDrunkard->GetFSM()->ChangeState(ForgetProblemsWithWhiskey::Instance());
	}
	else
	{
		//sleep
		pDrunkard->ResetDrunk();

		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "ZZZZ...";
	}
}

void GoFloorToSoberUp::Exit(Drunkard* pDrunkard) {}

bool GoFloorToSoberUp::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------StandUpAndGoOutside

StandUpAndGoOutside* StandUpAndGoOutside::Instance()
{
	static StandUpAndGoOutside instance;

	return &instance;
}

void StandUpAndGoOutside::Enter(Drunkard* pDrunkard)
{
	if (pDrunkard->Location() != outside)
	{
		pDrunkard->ChangeLocation(outside);

		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Trying somehow to go outside";
	}
}

void StandUpAndGoOutside::Execute(Drunkard* pDrunkard) {}

void StandUpAndGoOutside::Exit(Drunkard* pDrunkard)
{
	pDrunkard->IncreaseDrunk();

	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "I hate this saloon security! Hiips... Maybe I should go sleep";
}

bool StandUpAndGoOutside::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_DontComeToSaloon:

		cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID()) << " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": Has some difficulty standing";

		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": Saloon security is starting to get close to Tim";

		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pDrunkard->ID(), ent_Miner_Bob, Msg_GetDownToBusiness, NO_ADDITIONAL_INFO);

		pDrunkard->GetFSM()->ChangeState(GoFloorToSoberUp::Instance());

		return true;

	case Msg_GoSleep:

		cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID()) << " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": We'll see each other again! Hiips...";

		return true;
	}//end switch

	return false; //send message to global message handler
}
