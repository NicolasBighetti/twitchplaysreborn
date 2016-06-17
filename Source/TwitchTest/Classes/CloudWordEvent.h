// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "TwitchPlaysAPI.h"
#include "TwitchEvent.h"
/**
 * 
 */
class CloudWordEvent : public TwitchEvent
{
private:
	TMap<FString, int32> count;
	int32 nb_word;
	FTimerDelegate del;

public:
	CloudWordEvent(int32 _delay, GameContext* _context, AActorTwitchEventListener* _listener, UWorld* _world, int32 _nbword) :
		TwitchEvent(_delay, _context, _listener, _world),nb_word(_nbword)
	{
		UE_LOG(LogTemp, Warning, TEXT("CloudWordEvent %d"), nb_word);
		
		// Declare function to call on every timer tick
		CloudWordEvent* copy = this;
		del.BindLambda([copy] {
			TArray<FString> result;
			
			// Sort int by max
			copy->count.ValueSort([](int32 A, int32 B) {
				return A > B;
			});
			
			int i = 0;
			for (auto It = copy->count.CreateConstIterator(); It && i < copy->nb_word; ++It, i++)
				result.Add(It.Key());
			
			// Notify the listener
			copy->listener->updateCloudWord(result);
			copy->running = false;
		});

		// Start world timer
		if (world != NULL)
			world->GetTimerManager().SetTimer(Timer, del, delay, false);
	};

	void notify() override;
	void receiveMessage(FString userName, FString message) override;
};
