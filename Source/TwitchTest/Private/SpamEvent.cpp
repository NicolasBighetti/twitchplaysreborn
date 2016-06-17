// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchPlaysAPI.h"
#include "SpamEvent.h"

void SpamEvent::notify()
{
	int32 max = 0;
	int32 i;

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
	//if message equal word
	int camps;
	if (message.Equals(word)) {
		if (count.Num() == 1) {
			camps = 1;
		}
		else {
			camps = Context->GetCamps()->GetCampByPseudo(userName);
		}
		//if username belong to camp
		if (camps > 0) {
			count[--camps]++;
		}
	}
}
