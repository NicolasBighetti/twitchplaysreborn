#pragma once

#include "TwitchTest.h"
#include "Camps.h"

class TWITCHTEST_API CampsManager {

public:
	static const int AUTO_STRICT;
	static const int AUTO_LAX;
	static const int MANUAL;
	static const int LAX_THRESHOLD;

	uint32 AddPlayer(FString pseudo, int AUTOTEAM_POLICY, int team);
	bool AddPlayerToTeam(FString pseudo, int team);
	void BalanceTeam();
	bool IsBalanced();

	int GetCampByPseudo(FString pseudo);
private:
		TArray<Camps> CampsList;
		uint32 AveragePlayers;

		void setAverage(uint32 avrg) { AveragePlayers = avrg; };
		uint32 getAverage() { return AveragePlayers; };

		Camps GetByPopulation(uint32 pop);

		uint32 ComputeAverage();
		uint32 LowestTeam();
		
};
