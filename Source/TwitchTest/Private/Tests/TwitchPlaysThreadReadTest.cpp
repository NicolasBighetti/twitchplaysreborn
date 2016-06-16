#include "TwitchPlaysAPI.h"
#include "AutomationTest.h"
#include "ThreadRead.h"
#include "AssertionMacros.h"
#include "CommandRegistry.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TwitchPlaysThreadReadTest, "TwitchPlays.ThreadReadTest", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter);

// Running test
bool TwitchPlaysThreadReadTest::RunTest(const FString& Parameters)
{
	FCommandRegistry* r = new FCommandRegistry();
	ThreadRead* t = new ThreadRead(r);

	TWITCH_CHECK(t->Init(), "Error ThreadRead init()");
	
    return true;
}
