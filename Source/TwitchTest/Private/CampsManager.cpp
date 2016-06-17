#include "TwitchPlaysAPI.h"
#include "CampsManager.h"

// Team auto-balancing possibilities.
const int CampsManager::AUTO_STRICT = 0;
const int CampsManager::AUTO_LAX = 1;
const int CampsManager::MANUAL = 2;
const int CampsManager::LAX_THRESHOLD = 2;

uint32 CampsManager::AddCamps(Camps* cmp)
{
	// Add camp to the list
	uint32 res = CampsList.Add(cmp);

	// Increase camp counter
	nb_camps++;

	return res;
}

bool CampsManager::AddPlayer(FString pseudo, int AUTOTEAM_POLICY, int team)
{
	// Check if player is not already in the team
	if (team <= 0 || IsAlreadyInATeam(pseudo))
		return false;

	// Manual dispatching
	if (AUTOTEAM_POLICY == CampsManager::MANUAL)
	{
		return AddPlayerToTeam(pseudo, team);
	}

	// Auto lax dispatching
	if (AUTOTEAM_POLICY == CampsManager::AUTO_LAX)
	{
		if ((ComputeAverage() - LowestTeam()) < CampsManager::LAX_THRESHOLD)
		{
			return AddPlayerToTeam(pseudo, team);
		}
		else
			AUTOTEAM_POLICY = CampsManager::AUTO_STRICT;
	}

	// Auto strict dispatching
	if (AUTOTEAM_POLICY == CampsManager::AUTO_STRICT)
	{
		try {
			int cmp = GetByPopulation(LowestTeam());
			return AddPlayerToTeam(pseudo, cmp);
		}
		catch (exception e)
		{
			return false;
		}
	}

	return false;
}

int CampsManager::RemovePlayer(FString pseudo, int team)
{
	// Check if player is in the team
	if (!IsAlreadyInATeam(pseudo))
		return 0;

	// Try to find the player team
	if (team < 1)
		return CampsList[GetCampByPseudo(pseudo) - 1]->RemovePlayer(pseudo);
	
	return CampsList[team - 1]->RemovePlayer(pseudo);
}

bool CampsManager::AddPlayerToTeam(FString pseudo, int team)
{
	// Check if player is in the team
	if (team > CampsList.Num() || team == 0 || IsAlreadyInATeam(pseudo))
		return false;

	return CampsList[team - 1]->AddPlayer(pseudo);
}

uint32 CampsManager::ComputeAverage()
{
	uint32 average = 0;

	// Sum number of players in every teams
	for (Camps* cpm : CampsList)
		average += cpm->GetTotalPlayer();

	// Compute average
	return FMath::CeilToInt(average / CampsList.Num());

}

uint32 CampsManager::LowestTeam() {
	TArray<uint32> min;

	// Get number of players in every team
	for (Camps* cpm : CampsList)
		min.Add(cpm->GetTotalPlayer());

	// Find the lowest
	min.Sort();
	return min[0];
}

int CampsManager::GetCampByPseudo(FString pseudo)
{
	int team = 0;

	for (Camps* cmp : CampsList)
	{
		for (FString member : cmp->GetPlayerList())
		{
			if (member.Equals(pseudo))
				return team + 1;
		}
		team++;
	}

	return -1;
}

int CampsManager::GetByPopulation(uint32 pop){

	int i = 0;
	for (Camps* cmp : CampsList)
	{
		if (cmp->GetTotalPlayer() == pop)
			return i + 1;
		else
			i++;
	}
	throw 42;
}

void CampsManager::BalanceTeam() {}

bool CampsManager::IsAlreadyInATeam(FString pseudo)
{
	for (Camps* c : CampsList)
	{
		if (c->GetPlayerList().Contains(pseudo))
			return true;
	}

	return false;
}

bool CampsManager::IsBalanced()
{
	return false;
}

BlockingQueue<FCommandParser>* CampsManager::getQueueInit()
{
	BlockingQueue<FCommandParser>* bq;

	for (int i = 0; i < CampsList.Num(); i++)
	{
		bq = CampsList[i]->GetQueueInit();
		if (bq != NULL)
		{
			return bq;
		}
	}
	
	return NULL;
}
