#include "TwitchPlaysAPI.h"
#include "AutomationTest.h"
#include "CampsManager.h"
#include "AssertionMacros.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTwitchPlaysCampsManagerTest, "TwitchPlays.CampsManager", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter);

// Running test
bool FTwitchPlaysCampsManagerTest::RunTest(const FString& Parameters)
{
	CampsManager c = CampsManager();

	//Test initial CampsManager condition
	//check(c.GetNbCamps() == 100000000);
	if (c.GetNbCamps() != 0)
		return false;


	if (c.AddPlayerToTeam("Test_Man", 1))
		return false;


	//Add one team and test accordingly

	c.AddCamps(new Camps("Test"));

	if (c.GetNbCamps() != 1)
		return false;

	c.AddPlayerToTeam("Test_Man", 1);

	if (!c.IsAlreadyInATeam("Test_Man"))
		return false;

	//Specific remove

	
	c.RemovePlayer("Test_Man", 1);

	if (c.IsAlreadyInATeam("Test_Man"))
		return false;

	//Unspecific remove
	c.AddPlayerToTeam("Test_Man", 1);
	c.RemovePlayer("Test_Man", -1);

	if (c.IsAlreadyInATeam("Test_Man"))
		return false;



	return true;
}
