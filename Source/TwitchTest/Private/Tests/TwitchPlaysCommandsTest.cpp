#include "TwitchPlaysAPI.h"
#include "AutomationTest.h"
#include "CommandRegistry.h"

/**
  * Custom command for tests.
  */
class FTwitchTestCommand : public FCommand {
public:
	int32 SomeValue = 68;

	FTwitchTestCommand(FString _name) : FCommand(_name) {};

	void Execute(FCommandParser parser) {
		SomeValue = 86;
	}
};

/**
  * Commands tests.
  */
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTwitchPlaysCommandsCommandParserTest, "TwitchPlays.Commands.CommandParserTest", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter);

bool FTwitchPlaysCommandsCommandParserTest::RunTest(const FString& Parameters)
{
	FCommandParser parser("BotTest", "Test TP 68 8.6");

	// Check parsing
	TWITCH_CHECK(parser.GetName().Equals("test"), "Name not equals !");
	TWITCH_CHECK(parser.Next().Equals("TP"), "First argument not equals !");
	TWITCH_CHECK(parser.NextInt() == 68, "Second argument not equals !");
	TWITCH_CHECK(parser.NextFloat() == 8.6f, "Third argument not equals !");

	return true;
}


/**
  * Commands parser tests.
  */
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
	TWITCH_CHECK(cmd.SomeValue == 86, "Execute failed !");

    return true;
}

/**
  * Commands registry tests.
  */
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTwitchPlaysCommandsCommandRegistryTest, "TwitchPlays.Commands.CommandRegistryTest", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter);

bool FTwitchPlaysCommandsCommandRegistryTest::RunTest(const FString& Parameters)
{
	FTwitchTestCommand* cmd = new FTwitchTestCommand("Test");
	FCommandRegistry registry;
	FCommandParser parser("BotTest", "Test");

	// Check initialization
	TWITCH_CHECK(!registry.IsCommand("Test"), "Command doesn't exists !");
	TWITCH_CHECK(registry.Get("Test") == NULL, "Command doesn't exists ! (2)");
	TWITCH_CHECK(!FCommandRegistry::ExistsCommand("Test"), "Command doesn't exists ! (3)"); // Global

	// Add commands
	registry.Register(cmd);
	TWITCH_CHECK(registry.IsCommand("Test"), "Command should exists !");
	TWITCH_CHECK(registry.Get("Test") != NULL, "Command should exists ! (2)");
	TWITCH_CHECK(FCommandRegistry::ExistsCommand("Test"), "Command should exists ! (3)"); // Global

	// Execute command
	registry.Execute(parser);
	TWITCH_CHECK(cmd->SomeValue == 86, "Execute failed !");

	return true;
}

