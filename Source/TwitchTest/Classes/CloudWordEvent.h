// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "TwitchPlaysAPI.h"
#include "TwitchEvent.h"
/**
 * 
 */
class TWITCHTEST_API CloudWordEvent : public TwitchEvent
{
private:
	TMap<FString, int32> count;
	int32 nb_word;
	FTimerDelegate del;
public:

	CloudWordEvent(int32 _delay, GameContext* _context, AActorTwitchEventListener* _listener, UWorld* _world, int32 _nbword) :
		TwitchEvent(_delay, _context, _listener, _world),nb_word(_nbword) {
		//UE_LOG(LogTemp, Warning, TEXT("CloudWordEvent %d"), nb_word);
		CloudWordEvent* copy = this;
		del.BindLambda([copy] {
			//UE_LOG(LogTemp, Warning, TEXT("fin timer"));
			TArray<FString> result;
			//sort int by max
			copy->count.ValueSort([](int32 A, int32 B) {
				return A > B;
			});
			int i = 0;
			for (auto It = copy->count.CreateConstIterator(); It && i < copy->nb_word; ++It, i++)
			{
				result.Add(It.Key());
			}
			copy->listener->updateCloudWord(result);
			copy->running = false;
		});
		if (world != NULL) {
			//UE_LOG(LogTemp, Warning, TEXT("world not null"));
			world->GetTimerManager().SetTimer(Timer, del, delay, false);
		}
	};

	void notify() override;
	void receiveMessage(FString userName, FString message) override;
};
