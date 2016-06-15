#include "TwitchPlaysAPI.h"
#include "AutomationTest.h"
#include "AssertionMacros.h"
#include "Config.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TwitchPlaysConfigTest, "TwitchPlays.ConfigTest", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter);

// Running test
bool TwitchPlaysConfigTest::RunTest(const FString& Parameters)
{

	UE_LOG(LogTemp, Display, TEXT("TwitchPlaysConfigTest5"));

	Config Conf = Config::Load("Config/TwitchPlaysAPITest.conf");

	FString Test1 = Conf.Get("test");
	int Test2 = Conf.GetInt("test2");
	float Test3 = Conf.GetFloat("test3");

	TWITCH_CHECK(Test1 == "azerty", "Error on Get()");
	TWITCH_CHECK(Test2 == 42, "Error on GetInt()");
	TWITCH_CHECK(Test3 == 4242, "Error on GetFloat()");
	
    return true;
}