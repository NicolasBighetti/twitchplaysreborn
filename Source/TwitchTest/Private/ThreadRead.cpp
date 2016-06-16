#include "TwitchPlaysAPI.h"
#include "ThreadRead.h"

#define STOP_COMMAND "stop"

ThreadRead::ThreadRead(FCommandRegistry* Commands) {

	CommandsRegistry = Commands;
	queue = &FTwitchMessageReceiver::Queue;

}
bool ThreadRead::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Twitch Read : Init"));
	queue->clear();
	return true;
}

uint32 ThreadRead::Run()
{
	FString message;

	// Infinite loop
	while (running)
	{
		// Get command from queue
		FCommandParser parser = queue->pop();
		FString name = parser.GetName();

		// Check stop command
		if (name.Equals(TEXT(STOP_COMMAND)) && !running)
		{
			queue->clear();
			break;
		}

		// Execute command in game thread
		FFunctionGraphTask::CreateAndDispatchWhenReady([this, name, parser]() {
			UE_LOG(LogTemp, Warning, TEXT("Ball-> Executing command: %s"), *name);

			// Execute command
			if (!CommandsRegistry->Execute(parser))
				UE_LOG(LogTemp, Warning, TEXT("Ball-> Unknown command: %s"), *name);
		}
		, TStatId(), nullptr, ENamedThreads::GameThread);
	}

	return EXIT_SUCCESS;
}
void ThreadRead::Stop()
{
	running = false;
	queue->push(FCommandParser(TEXT("UE"), TEXT("stop")));
	UE_LOG(LogTemp, Warning, TEXT("Twitch Read: Stop"));
	//delete(queue);
}

void ThreadRead::SetQueue(BlockingQueue<FCommandParser>* Bqueue)
{
	queue = Bqueue;
}

