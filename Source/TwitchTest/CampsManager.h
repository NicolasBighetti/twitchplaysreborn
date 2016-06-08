#pragma once

#include "TwitchTest.h"
#include "Camps.h"
#include "BlockingQueue.h"

class TWITCHTEST_API CampsManager {

public:

	CampsManager(int nbCamps);

	static const int AUTO_STRICT;
	static const int AUTO_LAX;
	static const int MANUAL;
	static const int LAX_THRESHOLD;

	bool AddPlayer(FString pseudo, int AUTOTEAM_POLICY, int team);
	int RemovePlayer(FString pseudo, int team);
	bool AddPlayerToTeam(FString pseudo, int team);
	void BalanceTeam();
	bool IsBalanced();

	BlockingQueue<FString>* getQueue();

	int GetCampByPseudo(FString pseudo);
private:
		TArray<Camps> CampsList;
		uint32 AveragePlayers = 0;

		void setAverage(uint32 avrg) { AveragePlayers = avrg; };
		uint32 getAverage() { return AveragePlayers; };

		int GetByPopulation(uint32 pop);

		uint32 ComputeAverage();
		uint32 LowestTeam();
		
};
