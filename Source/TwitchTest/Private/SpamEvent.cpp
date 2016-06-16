// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchPlaysAPI.h"
#include "SpamEvent.h"


void SpamEvent::notify()
{
	UE_LOG(LogTemp, Warning, TEXT("fin timer"));
	int32 max = 0;
	int32 i;
	//UE_LOG(LogTemp, Warning, TEXT("notify"));

	//iterate and get the max occurency
	for (i = 0; i < count.Num(); ++i) {
		if (count[i] > max) {
			max = i;
		}
	}
	//update listener
	if (listener != NULL) {
		listener->updateSpam(++max, count[max]);
	}
	running = false;
}

void SpamEvent::receiveMessage(FString userName, FString message)
{
	UE_LOG(LogTemp, Warning, TEXT("Event receive before equals %s:%s"),*message,*word);
	//if message equal word
	int camps;
	if (message.Equals(word)) {
		if (count.Num() == 1) {
			camps = 1;
			//UE_LOG(LogTemp, Warning, TEXT("SpamEvent une team %d"), camps);
		}
		else {
			camps = Context->GetCamps()->GetCampByPseudo(userName);
			UE_LOG(LogTemp, Warning, TEXT("SpamEvent dans team %d"), camps);
		}
		//if username belong to camp
		if (camps > 0) {
			UE_LOG(LogTemp, Warning, TEXT("SpamEvent dans team %d"), camps);
			count[--camps]++;
		}
			
	}
}

