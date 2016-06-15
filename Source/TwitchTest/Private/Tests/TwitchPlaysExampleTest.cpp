#include "TwitchPlaysAPI.h"
#include "AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTwitchPlaysExampleTest, "TwitchPlays.ExampleTest", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter);

// Running test
bool FTwitchPlaysExampleTest::RunTest(const FString& Parameters)
{
	UE_LOG(LogTemp, Display, TEXT("Twitch Plays example test ! <3"));
    return true;
}

/*
How to run a test in Unreal Engine :
	In Unreal Editor console :
		"Automation List" => List all tests
		"Automation RunTests TwitchPlays.ExampleTest" => Run TwitchPlays.ExampleTest

That's all for me ! **drop the mic**
*/
