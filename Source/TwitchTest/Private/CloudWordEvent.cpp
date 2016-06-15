// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchPlaysAPI.h"
#include "CloudWordEvent.h"

void CloudWordEvent::notify()
{
	
	TArray<FString> result;
	//sort int by max
	count.ValueSort([](int32 A, int32 B) {
		return A > B; 
	});
	int i = 0;
	for (auto It = count.CreateConstIterator(); It && i < nb_word; ++It,i++)
	{
		result.Add(It.Key());
	}
	listener->updateCloudWord(result);
	running = false;
}

void CloudWordEvent::receiveMessage(FString userName, FString message)
{
	if (!message.Contains(TEXT(" "))) {
		//if message equal word
		if (!count.Contains(message)) {
			count.Add(message, 1);
		}
		else {
			count[message]++;
		}
	}
}