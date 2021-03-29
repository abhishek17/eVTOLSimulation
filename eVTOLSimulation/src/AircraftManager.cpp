#include"AircraftManager.h"

//Constructor
AircraftManager::AircraftManager()
{
	//Initialize stats
	mAvgTimeInFlight = 0.0f;
	mAvgTimeCharging = 0.0f;
	mAvgTimeWaiting = 0.0f;
	mMaxNumFaults = 0;
	mTotalDistanceTraveled = 0.0f;
}

//Destructor
AircraftManager::~AircraftManager()
{
	for (Aircraft* Plane : mFleet)
	{
		if (Plane != nullptr)
		{
			delete(Plane);
		}
	}
	mFleet.empty();
}

//Adds an airplane: Input is chargers and the plane that gets added is retruned as an output.
bool AircraftManager::AddAircraft(Charger *Chargers[MAX_CHARGERS], Aircraft* & PlaneDeployed)
{
	Aircraft* NewPlane = new Aircraft(mCompany, mFleet.size());
	if (NewPlane == nullptr)
	{
		std::cout << "ERROR!! Can`t deploy an airplane" << std::endl;
		return false;
	}
	if (Chargers == nullptr)
	{
		std::cout << "ERROR!! Can`t deploy and airplane without access to chargers"<<std::endl;
		return false;
	}
	NewPlane->Init(Chargers);
	mFleet.push_back(NewPlane);
	PlaneDeployed = NewPlane;
	return true;

}

//print stats of a particular company
void AircraftManager::PrintStats()
{
	float TotalTimeInFlight = 0.0f;
	float TotalTimeCharging = 0.0f;
	float TotalTimeWaitingToCharge = 0.0f;
	for (Aircraft *CurrAircraft : mFleet)
	{
		TotalTimeInFlight += CurrAircraft->GetTimeInFlight();
		TotalTimeCharging += CurrAircraft->GetTimeInCharging();
		TotalTimeWaitingToCharge += CurrAircraft->GetTimeWaitingToCharge();

		mMaxNumFaults += CurrAircraft->GetNumFaults();
		mTotalDistanceTraveled += CurrAircraft->GetPassengerDistanceTraveled();
	}

	float NumPlanes = static_cast<float>(mFleet.size());
	if (NumPlanes == 0.0f) //No planes were deployed from this company
	{
		mAvgTimeCharging = 0.0f;
		mAvgTimeInFlight = 0.0f;
		mAvgTimeWaiting = 0.0f;
	}
	else
	{
		mAvgTimeCharging = TotalTimeCharging / NumPlanes;
		mAvgTimeInFlight = TotalTimeInFlight / NumPlanes;
		mAvgTimeWaiting = TotalTimeWaitingToCharge / NumPlanes;
	}
	

	std::cout << "Simulation stats for company: " << EnumStringsCompany[static_cast<int>(mCompany)] << std::endl;
	std::cout << "Number of aircrafts deployed: " << NumPlanes << std::endl;
	std::cout << "Average time (hours) spent in charging: " << mAvgTimeCharging << std::endl;
	std::cout << "Average time (hours) spent in air: " << mAvgTimeInFlight << std::endl;
	std::cout << "Average time (hours) spent waiting to charge: " << mAvgTimeWaiting << std::endl;
	std::cout << "Maximum number of faults: " << mMaxNumFaults << std::endl;
	std::cout << "Total distance travelled (miles) by passengers: " << mTotalDistanceTraveled << std::endl;
	std::cout << ".........End of Summary of this type.........." << std::endl << std::endl;
}