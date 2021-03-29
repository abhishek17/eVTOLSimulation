#ifndef AIRCRAFT_MANAGER
#define AIRCRAFT_MANAGER

#include<vector>
#include"Aircraft.h"

//This class manages all the aircrafts of a particular company
class AircraftManager
{

private:
	std::vector<Aircraft*> mFleet;
	Company mCompany;

	//Simulation record
	float mAvgTimeInFlight;
	float mAvgTimeCharging;
	float mAvgTimeWaiting;
	unsigned int mMaxNumFaults;
	float mTotalDistanceTraveled;

public: 
	AircraftManager();
	~AircraftManager();
	inline void SetCompany(Company Comp)
	{
		mCompany = Comp;
	}

	//Getter functions
	inline Aircraft* GetAirplane(unsigned int Index)
	{
		return mFleet.at(Index);
	}
	inline unsigned int GetNumAirplanes()
	{
		return mFleet.size();
	}

	//Adds an airplane: Input is chargers and the plane that gets added is retruned as an output.
	bool AddAircraft(Charger *Chargers[MAX_CHARGERS], Aircraft* & PlaneDeployed);

	//print stats of a particular company
	void PrintStats();
};

#endif //AIRCRAFT_MANAGER
