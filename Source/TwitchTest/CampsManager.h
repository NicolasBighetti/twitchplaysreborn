#pragma once

#include "Camps.h"

class TWITCHTEST_API CampsManager {

public:
	bool AddPlayer(FString pseudo);
	uint32 AddPlayer(FString pseudo, int team, uint32 AUTOTEAM_POLICY);

	enum BALANCEPOLICY { AUTO_STRICT, AUTO_LAX, MANUAL};

	private
		TArray<Camps> CampsList;

};
