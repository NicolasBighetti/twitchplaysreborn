#include "TwitchPlaysAPI.h"
#include "AutomationTest.h"
#include "CampsManager.h"
#include "AssertionMacros.h"
#include "BlockingQueue.h"
#include "Command.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTwitchPlaysCampsTest, "TwitchPlays.Camps", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter);

// Running test
bool FTwitchPlaysCampsTest::RunTest(const FString& Parameters)
{

	Camps c = Camps("Test");


	//Test name
	
	if (c.GetName().Compare("Test") != 0)
		return false;
	
	//Initial empty
	if (c.GetTotalPlayer() != 0) {
		return false;
	}


	//Queue init only once

	BlockingQueue<FCommandParser>* q;

	q = c.GetQueueInit();

	if (q == NULL)
		return false;

	q = c.GetQueueInit();

	if (!q == NULL)
		return false;

	//player management

	c.AddPlayer("Test");


	if (!c.IsInTeam("Test"))
		return false;
	if (c.IsInTeam("Tast"))
		return false;

	//remove
	c.RemovePlayer("Test");

	if (c.IsInTeam("Test"))
		return false;

	//Multiple player
	c.AddPlayer("Test");
	c.AddPlayer("Tast");
	c.AddPlayer("Tust");

	if (c.GetTotalPlayer() != 3)
		return false;

	if (!(c.GetPlayerList().Contains("Test") && c.GetPlayerList().Contains("Tast") && c.GetPlayerList().Contains("Tust")))
		return false;

	q = c.GetQueue();

	if (q == NULL)
		return false;

	return true;
}