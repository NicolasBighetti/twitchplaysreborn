// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "Strategy.h"

TMap<FString, int32> Strategy::StrategyMap = BasicStrategyMap();

// ===

Strategy::Strategy(BlockingQueue<FCommandParser>* _queue, GameContext* _context) : queue(_queue), Context(_context)
{
	int nb = Context->GetCamps()->GetNbCamps();
	multicamps = (nb > 1);

	UE_LOG(LogTemp, Warning, TEXT("constructeur : multi camps test %d, %d"), nb, multicamps);

	for (int i = 0; i < nb; i++)
		Messages.Add(TMap<FString, FCommandParser>());
}

void Strategy::Receive(FCommandParser parser) {
	int cmp = 1;

	if (multicamps) {
		cmp = Context->GetCamps()->GetCampByPseudo(parser.GetUserName());
		UE_LOG(LogTemp, Warning, TEXT("multi camps test %d"), cmp);
	}
	if (cmp > 0) {
		UE_LOG(LogTemp, Warning, TEXT("test dans strategy receive %d"), cmp);
		//Messages[cmp-1].Add(parser.GetUserName(), parser);
		Context->GetCamps()->getCamps(cmp)->GetQueue()->push(parser);
		//queue->push(message);
	}
}

void Strategy::OnTick() {}
