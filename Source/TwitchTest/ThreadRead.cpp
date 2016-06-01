#include "TwitchTest.h"
#include "ThreadRead.h"


ThreadRead::ThreadRead(BlockingQueue<FString>* q) {
	queue=q;

}
bool ThreadRead::Init()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Init thread");
	return true;
}
uint32 ThreadRead::Run()
{
	FString message;
	while (true) {
		message = queue->pop();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "reception "+message);
		//UE_LOG(LogTemp, Warning, TEXT("%s"),message);
	}
	return 1;
}
void ThreadRead::Stop()
{
	
}