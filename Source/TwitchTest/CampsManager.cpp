#include "TwitchTest.h"
#include "CampsManager.h"


const int CampsManager::AUTO_STRICT = 0;
const int CampsManager::AUTO_LAX = 1;
const int CampsManager::MANUAL = 2;

const int CampsManager::LAX_THRESHOLD = 2;

CampsManager::CampsManager(int nbCamps) {

	if (nbCamps <= 0)
		nbCamps = 1;

	for (int i = 0; i < nbCamps; i++)
		CampsList.Add(Camps());
}

bool CampsManager::AddPlayer(FString pseudo, int AUTOTEAM_POLICY, int team)
{
	if (team <= 0)
		return false;

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
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, pseudo.Append(" Lowest : ").Append(FString::FromInt(LowestTeam()).Append(" Average : ").Append(FString::FromInt(ComputeAverage()))));
			int cmp;
			try {

				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, pseudo.Append(" Lowest : ").Append(FString::FromInt(LowestTeam()).Append(" Average : ").Append(FString::FromInt(ComputeAverage()))));

				cmp = GetByPopulation(LowestTeam());
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, pseudo.Append("Added to camp ").Append(FString::FromInt(cmp)));
				return AddPlayerToTeam(pseudo, cmp);
				
			}
			catch (exception e)
			{
				return false;
			}
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "END OF SHIT");
	return false;
}

int CampsManager::RemovePlayer(FString pseudo, int team)
{
	if (team < 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::FromInt(GetCampByPseudo(pseudo)-1));
		return CampsList[GetCampByPseudo(pseudo)-1].RemovePlayer(pseudo);
	}

	return CampsList[team-1].RemovePlayer(pseudo);
}


bool CampsManager::AddPlayerToTeam(FString pseudo, int team)
{
	if (team > CampsList.Num() || team == 0)
		return false;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, pseudo.Append(FString::FromInt(0).Append(" ").Append(FString::FromInt(team-1))));
	return CampsList[team-1].AddPlayer(pseudo);
}

uint32 CampsManager::ComputeAverage()
{
	uint32 average = 0;
	int i = 0;
	for (Camps cpm : CampsList)
	{
		i++;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::FromInt(average).Append("Computing average... Iteration : ").Append(FString::FromInt(i)));
		average += cpm.GetTotalPlayer();
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::FromInt(FMath::CeilToInt(average / CampsList.Num())));
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

int CampsManager::GetByPopulation(uint32 pop){

	int i = 0;
	for (Camps cmp : CampsList)
	{
		if (cmp.GetTotalPlayer() == pop)
			return i+1;
		else
			i++;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, "SHITS THE BED YO");
	throw 42;
}

void CampsManager::BalanceTeam()
{

}

bool CampsManager::IsBalanced()
{
	return false;
}

BlockingQueue<FString>* CampsManager::getQueue()
{
	BlockingQueue<FString>* bq;

	for (Camps cmp : CampsList)
	{
		bq = cmp.GetQueue();
		if (bq != NULL)
			return bq;
	}
	return NULL;
}
