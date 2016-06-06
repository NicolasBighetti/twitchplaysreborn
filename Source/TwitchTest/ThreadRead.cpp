#include "TwitchTest.h"
#include "ThreadRead.h"


ThreadRead::ThreadRead(FCommandRegistry* Commands) {

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

	FString message;
	/*
	queue->push(TEXT("salut"));
	UE_LOG(LogTemp, Warning, TEXT("Ball-> test queue: %s"), *queue->pop());
	*/
	while (running) {
		FString cmd;
		cmd = queue->pop();
		/*
		if (!CommandsQueue.IsEmpty())
		{
			// Get twitch command
			FString cmd;
			CommandsQueue.Dequeue(cmd);
			*/
			UE_LOG(LogTemp, Warning, TEXT("Ball-> Executing command: %s"), *cmd);
			if (cmd.Equals(TEXT("stop"))) {
				queue->clear();
				break;
			}
			// Execute command
			if (!CommandsRegistry->Execute(cmd))
				// Command not found
				UE_LOG(LogTemp, Warning, TEXT("Ball-> Unknown command: %s"), *cmd);
		
		FPlatformProcess::Sleep(1);
		UE_LOG(LogTemp, Warning, TEXT("it"));
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