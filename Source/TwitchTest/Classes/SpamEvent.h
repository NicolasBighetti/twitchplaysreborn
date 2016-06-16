// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TwitchPlaysAPI.h"
#include "TwitchEvent.h"
/**
 * 
 */
class TWITCHTEST_API SpamEvent : public TwitchEvent
{
private:
	FString word;
	TArray<int32> count;
	FTimerDelegate del;
public:
	SpamEvent() {

	}
	SpamEvent(int32 _delay, GameContext* _context, AActorTwitchEventListener* _listener, UWorld* _world,FString _word) : TwitchEvent(_delay, _context, _listener, _world) {
		word = _word;
		UE_LOG(LogTemp, Warning, TEXT("Spam debut : %s %d"), *word, Context->GetCamps()->GetNbCamps());
		count.Init(0, Context->GetCamps()->GetNbCamps());
		//notify();
		AActorTwitchEventListener* listen = listener;
		SpamEvent* copy = this;
		del.BindLambda([listen,copy] {
			UE_LOG(LogTemp, Warning, TEXT("fin timer"));
			int32 max = 0;
			int32 i;
			UE_LOG(LogTemp, Warning, TEXT("notify"));

			//iterate and get the max occurency
			for (i = 0; i < copy->count.Num(); ++i) {
				if (copy->count[i] > max) {
					max = i;
				}
			}
			copy->running = false;
			if (listen != NULL) {
				int32 strenght = copy->count[max];
				listen->updateSpam(++max,strenght);
			}
		});


		if(world!=NULL){
			//UE_LOG(LogTemp, Warning, TEXT("world not null"));
			world->GetTimerManager().SetTimer(Timer, del, delay, false);
		}
		
	};

	void notify() override;
	void receiveMessage(FString userName, FString message) override;
};
