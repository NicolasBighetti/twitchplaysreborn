#include "TwitchPlaysAPI.h"
#include "AutomationTest.h"
#include "CommandRegistry.h"

class FTwitchTestCommand : public FCommand {
public:
	int32 SomeValue = 68;

	FTwitchTestCommand(FString _name) : FCommand(_name) {};

	void Execute(FCommandParser parser) {
		SomeValue = 86;
	}
};


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTwitchPlaysCommandsCommandTest, "TwitchPlays.Commands.CommandTest", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter);

bool FTwitchPlaysCommandsCommandTest::RunTest(const FString& Parameters)
{
	FTwitchTestCommand cmd("Test <3");
	FCommandParser parser;

	// Check initialization
	TWITCH_CHECK(cmd.GetName().Equals("Test <3"), "Name not equals !");
	TWITCH_CHECK(cmd.SomeValue == 68, "Initialization error !");

	// Execute command
	cmd.Execute(parser);

	// Check value changed
	TWITCH_CHECK(cmd.SomeValue == 86, "Execute failed !");

    return true;
}
