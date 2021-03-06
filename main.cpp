#include <fstream>
#include <time.h>
#include <thread>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "Drunkard.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"

std::ofstream os;

void ExecuteEntity(BaseGameEntity* entity)
{
	entity->Update();
}

int main()
{
	//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
	os.open("output.txt");
#endif

	//seed random number generator
	srand((unsigned)time(NULL));

	//create a miner
	Miner* Bob = new Miner(ent_Miner_Bob);

	//create his wife
	MinersWife* Elsa = new MinersWife(ent_Elsa);

	//create a drunkard
	Drunkard* Tim = new Drunkard(ent_Tim);

	//register them with the entity manager
	EntityMgr->RegisterEntity(Bob);
	EntityMgr->RegisterEntity(Elsa);
	EntityMgr->RegisterEntity(Tim);

	//run Bob and Elsa through a few Update calls
	for (int i = 0; i < 30; ++i)
	{
		/*Bob->Update();
		Elsa->Update();
		Tim->Update();*/

		std::thread threadBob(&ExecuteEntity, Bob);
		std::thread threadElsa(&ExecuteEntity, Elsa);
		std::thread threadTim(&ExecuteEntity, Tim);

		threadBob.join();
		threadElsa.join();
		threadTim.join();
		
		//dispatch any delayed messages
		Dispatch->DispatchDelayedMessages();

		Sleep(800);
	}

	//tidy up
	delete Bob;
	delete Elsa;
	delete Tim;

	//wait for a keypress before exiting
	PressAnyKeyToContinue();

	return 0;
}
