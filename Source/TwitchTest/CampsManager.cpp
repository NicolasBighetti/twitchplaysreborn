#include "TwitchTest.h"
#include "CampsManager.h"


const int CampsManager::AUTO_STRICT = 0;
const int CampsManager::AUTO_LAX = 1;
const int CampsManager::MANUAL = 2;

const int CampsManager::LAX_THRESHOLD = 2;

uint32 CampsManager::AddPlayer(FString pseudo, int AUTOTEAM_POLICY, int team)
{

	if (AUTOTEAM_POLICY == CampsManager::MANUAL)
	{
		return AddPlayerToTeam(pseudo, team);
	}

	if (AUTOTEAM_POLICY == CampsManager::AUTO_LAX)
	{
		if ((ComputeAverage() - LowestTeam()) < CampsManager::LAX_THRESHOLD)
		{
			return AddPlayerToTeam(pseudo, team);
		}
		else
			AUTOTEAM_POLICY = CampsManager::AUTO_STRICT;
	}

	if (AUTOTEAM_POLICY == CampsManager::AUTO_STRICT)
	{
		if (LowestTeam() < ComputeAverage())
		{
			Camps cmp;
			try {
				cmp = GetByPopulation(LowestTeam());
				cmp.AddPlayer(pseudo);
				return true;
			}
			catch (exception e)
			{
				return false;
			}
		}
		else
		{
			CampsList[0].AddPlayer(pseudo);
		}
	}

	return false;
}


bool CampsManager::AddPlayerToTeam(FString pseudo, int team)
{
	if (team > CampsList.Num())
		return false;

	return CampsList[team-1].AddPlayer(pseudo);
}

uint32 CampsManager::ComputeAverage()
{
	uint32 average = 0;

	for (Camps cpm : CampsList)
	{
		average += cpm.GetTotalPlayer();
	}

	return FMath::CeilToInt(average / CampsList.Num());

}

uint32 CampsManager::LowestTeam() {
	TArray<uint32> min;

	for (Camps cpm : CampsList)
	{
		min.Add(cpm.GetTotalPlayer());
	}

	min.Sort();

	return min[0];
}

int CampsManager::GetCampByPseudo(FString pseudo)
{
	int team = 0;

	for (Camps cmp : CampsList)
	{
		for (FString member : cmp.GetPlayerList())
		{
			if (member.Equals(pseudo))
				return team+1;
		}
		team++;
	}

	return -1;
}

Camps CampsManager::GetByPopulation(uint32 pop){
	for (Camps cmp : CampsList)
	{
		if (cmp.GetTotalPlayer() == pop)
			return cmp;
	}

	throw 42;
}

void CampsManager::BalanceTeam()
{

}

bool CampsManager::IsBalanced()
{
	return false;
}
