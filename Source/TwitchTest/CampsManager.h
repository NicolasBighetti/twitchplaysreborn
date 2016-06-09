#pragma once

#include "TwitchTest.h"
#include "Camps.h"
#include "BlockingQueue.h"

class TWITCHTEST_API CampsManager {

public:

	static const int AUTO_STRICT;
	static const int AUTO_LAX;
	static const int MANUAL;
	static const int LAX_THRESHOLD;

	uint32 AddCamps(Camps* cmp);
	bool AddPlayer(FString pseudo, int AUTOTEAM_POLICY, int team);
	int RemovePlayer(FString pseudo, int team);
	bool AddPlayerToTeam(FString pseudo, int team);
	void BalanceTeam();
	bool IsBalanced();
	bool IsAlreadyInATeam(FString pseudo);
	BlockingQueue<FString>* getQueueInit();
	int GetNbCamps() {
		return nb_camps;
	}

	BlockingQueue<FString>* getQueueInit(int i) {
		return CampsList[i - 1]->GetQueueInit();
	}

	int GetCampByPseudo(FString pseudo);

	Camps* getCamps(int nb) {
		return CampsList[nb - 1];
	}

private:
		TArray<Camps*> CampsList;
		uint32 AveragePlayers = 0;
		uint32 nb_camps = 0;
		void setAverage(uint32 avrg) { AveragePlayers = avrg; };
		uint32 getAverage() { return AveragePlayers; };

		int GetByPopulation(uint32 pop);

		uint32 ComputeAverage();
		uint32 LowestTeam();
		
};
