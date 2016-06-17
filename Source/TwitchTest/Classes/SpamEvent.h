// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TwitchPlaysAPI.h"
#include "TwitchEvent.h"
/**
 * 
 */
class SpamEvent : public TwitchEvent
{
private:
	FString word;
	TArray<int32> count;
	FTimerDelegate del;
public:
	SpamEvent() {}
	
	SpamEvent(int32 _delay, GameContext* _context, AActorTwitchEventListener* _listener, UWorld* _world,FString _word) 
		: TwitchEvent(_delay, _context, _listener, _world), word(_word)
	{
		UE_LOG(LogTemp, Warning, TEXT("Starting Spam event : %s %d"), *word, Context->GetCamps()->GetNbCamps());
		count.Init(0, Context->GetCamps()->GetNbCamps());
		
		// Declare listener
		AActorTwitchEventListener* listen = listener;
		SpamEvent* copy = this;
		
		// Declare function to call on timer tick
		del.BindLambda([listen,copy] {
			int32 max = 0;
			int32 i;

			// Iterate and get the max occurency
			for (i = 0; i < copy->count.Num(); ++i) {
				if (copy->count[i] > max) {
					max = i;
				}
			}
			
			copy->running = false;
			
			// Call the listener
			if (listen != NULL) {
				int32 strenght = copy->count[max];
				listen->updateSpam(++max, strenght);
			}
		});

		// Notify the listener
		if(world!=NULL)
			world->GetTimerManager().SetTimer(Timer, del, delay, false);
	};

	void notify() override;
	void receiveMessage(FString userName, FString message) override;
};
