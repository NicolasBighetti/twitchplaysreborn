#include "TwitchPlaysAPI.h"
#include "AutomationTest.h"
#include "CampsManager.h"
#include "AssertionMacros.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTwitchPlaysCampsBalanceTest, "TwitchPlays.CampsBalance", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter);

// Running test
bool FTwitchPlaysCampsBalanceTest::RunTest(const FString& Parameters)
{

	CampsManager c = CampsManager();

	c.AddCamps(new Camps("Pistache"));
	c.AddCamps(new Camps("Vanille"));
	c.AddCamps(new Camps("Sueur"));

	FString sup = "ABCDEFGHIJKLMNOPQRST";
	FString name = "PLAYER_";

	for (char ch : sup)
	{
		c.AddPlayer(name.AppendChar(ch), CampsManager::MANUAL, 1);
	}


	if (c.getCamps(1)->GetTotalPlayer() != 20)
		return false;


	CampsManager c2 = CampsManager();
	c2.AddCamps(new Camps("Chaleur"));
	c2.AddCamps(new Camps("Vestibule"));
	c2.AddCamps(new Camps("Module"));
	c2.AddCamps(new Camps("Escamotable"));

	sup = "ABCDEFGHIJKLMNOPQRST";
	name = "PLAYER_";

	for (char ch : sup)
	{
		c2.AddPlayer(name.AppendChar(ch), CampsManager::AUTO_STRICT, 1);
	}

	UE_LOG(LogTemp, Warning, TEXT("Testign auto balance"));
	if ((c2.getCamps(1)->GetTotalPlayer() != 5) || (c2.getCamps(2)->GetTotalPlayer() != 5) || (c2.getCamps(3)->GetTotalPlayer() != 5) || (c2.getCamps(4)->GetTotalPlayer() != 5))
		return false;

	return true;
}