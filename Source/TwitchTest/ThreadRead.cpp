#include "TwitchTest.h"
#include "ThreadRead.h"


ThreadRead::ThreadRead(FCommandRegistry<>* Commands) {
	CommandsRegistry = Commands;
}

bool ThreadRead::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("init thread read"));
	queue = &FTwitchMessageReceiver::Queue;
	queue->clear();
	return true;
}
uint32 ThreadRead::Run()
{
	// Infinite loop
	while (running)
	{
		// Get command from blocking queue
		FString cmd = queue->pop();

		// Check "stop" command
		if (cmd.Equals(TEXT("stop")) && running == false)
		{
			queue->clear();
			break;
		}

		// Check if the text is an actual command
		UE_LOG(LogTemp, Warning, TEXT("Ball-> Checking command: %s"), *cmd);
		if (!FCommandRegistry<>::ExistsCommand(cmd))
		{
			UE_LOG(LogTemp, Warning, TEXT("Ball-> Unknown command: %s"), *cmd);
			continue;
		}

		// Execute command in game thread
		FFunctionGraphTask::CreateAndDispatchWhenReady([this,cmd]() {
			UE_LOG(LogTemp, Warning, TEXT("Ball-> Executing command: %s"), *cmd);

			// Execute command
			if (!CommandsRegistry->Execute(cmd))
				UE_LOG(LogTemp, Warning, TEXT("Ball-> Unknown command: %s"), *cmd);
		}
		, TStatId(), nullptr, ENamedThreads::GameThread);

		// Debug message
		UE_LOG(LogTemp, Warning, TEXT("ThreadRead iteration!"));
	}

	return EXIT_SUCCESS;
}

void ThreadRead::Stop()
{
	running = false;
	queue->push(TEXT("stop"));
	UE_LOG(LogTemp, Warning, TEXT("Twitch Read: Stop"));
	//delete(queue);
}