// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchPlaysAPI.h"
#include "Anarchy.h"

void Anarchy::OnTick() {

	UE_LOG(LogTemp, Warning, TEXT("Anarchy OnTick"));
	int i;
	//on push la premiere commande présente dans les différentes maps
	for (i = 0 ; i < Context->GetCamps()->GetNbCamps(); i++) {
		auto It = Messages[i].CreateConstIterator();

		if (It) {
			Context->GetCamps()->getCamps(i+1)->GetQueue()->push(It.Value());
			Messages[i].Empty();
		}
	}
	
	/*
	auto It = Messages->CreateConstIterator();

	if (It) {
		queue->push(*It.Value());
		Messages->Empty();
	}
	*/
}


void Anarchy::Receive(FCommandParser parser) {

	int cmp = 1;
	//We check if there are more than one camp
	if (multicamps) {
		cmp = Context->GetCamps()->GetCampByPseudo(parser.GetUserName());
	}
	//if not present cmp = -1
	if (cmp > 0) {
		Messages[cmp - 1].Add(parser.GetUserName(), parser);
	}
}