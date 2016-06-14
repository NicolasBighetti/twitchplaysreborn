// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "Democracy.h"


void Democracy::OnTick() {

	UE_LOG(LogTemp, Warning, TEXT("Democracy OnTick"));
	int i;

	//we push all commands for all different maps
	for (i = 0; i < Context->GetCamps()->GetNbCamps(); i++) {
		auto It = Messages[i].CreateIterator();

		if (It) {
			//For all messages
			for (It; It; ++It)
			{
				FString command = *It.Value().GetName();

				//We check if command exist in the map
				int v = 0;
				v = commands.FindRef(command);

				//If already present, ++
				if (v != 0) {
					commands.Emplace(command, v + 1);
				}
				//Else we add it
				else {
					commands.Add(command, 1);
				}
			}

			//Find the more popular command
			auto It2 = commands.CreateIterator();
			FString command = It2.Key();
			int val = It2.Value();

			for (It2; It2; ++It2) {
				if (val < It2.Value())
					command = It2.Key();
			}

			//We send the command
			FCommandParser theCommand("FakePseudo", command);

			Context->GetCamps()->getCamps(i + 1)->GetQueue()->push(theCommand);
			//Clean
			Messages[i].Empty();
			commands.Empty();
		}
	}

}


void Democracy::Receive(FCommandParser parser) {

	int cmp = 1;
	//We check if there are more than one camp
	if (multicamps) {
		cmp = Context->GetCamps()->GetCampByPseudo(parser.GetUserName());
		//UE_LOG(LogTemp, Warning, TEXT("multi camps test %d"), cmp);
	}
	//if not present cmp = -1
	if (cmp > 0) {
		//UE_LOG(LogTemp, Warning, TEXT("test dans strategy receive %d"), cmp);
		Messages[cmp - 1].Add(parser.GetUserName(), parser);
	}
}