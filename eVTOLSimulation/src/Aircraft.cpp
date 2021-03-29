#include <chrono>
#include <assert.h>  
#include"Aircraft.h"

//Constructor
Aircraft::Aircraft(Company Type, unsigned int Id)
{
	mType = Type;
	mId = Id;

	mTimeInFlight = 0.0f;
	mTimeCharging = 0.0f;
	mTimeWaitingToCharge = 0.0f;
	mNumFaults = 0;
	mPassengerDistanceTraveled = 0.0f;
}

//Initialize an aircraft with shared resources and 
void Aircraft::Init(Charger *Chargers[MAX_CHARGERS])
{
	for (unsigned int i = 0; i < MAX_CHARGERS; i++)
	{
		mChargers[i] = Chargers[i];
		mChargerAcquired[i] = false;
	}
	mCurrBattery = BATTERY_CAPACITY[static_cast<int>(mType)];
	mState = AircraftState::InAir;
}

//This function randmonizes a fault based on the probablity and delta time
bool Aircraft::DidFaultOccur(float DeltaTimeHours)
{
	float ProbabilityDeltaTimeHundredScale = PROBABILITY_FAULT[static_cast<int>(mType)] * DeltaTimeHours * 100.f;
	srand(static_cast<int>(time(0)));
	return (static_cast<float>(rand() % 100) < ProbabilityDeltaTimeHundredScale);
	
}

//Update function to handle the charging state
void Aircraft::ChargingUpdate(float DeltaTimeHours)
{
	std::cout << "Aircraft Type: " << EnumStringsCompany[static_cast<int>(mType)] << " Id: " << mId << " currently charging" << std::endl;
	//Stat keeping
	mTimeCharging += DeltaTimeHours;

	// Calculate if the battery has been charged
	mCurrBattery += (BATTERY_CAPACITY[static_cast<int>(mType)] / TIME_TO_CHARGE[static_cast<int>(mType)]) * DeltaTimeHours;
	if (mCurrBattery >= BATTERY_CAPACITY[static_cast<int>(mType)])
	{
		for (int i = 0; i < MAX_CHARGERS; i++)
		{
			assert(mChargers[i] != nullptr);
			if (mChargerAcquired[i])
			{
				mChargers[i]->Release();
				mChargerAcquired[i] = false;
			}

		}
		mState = AircraftState::InAir;
	}
}

//Update function to handle the In-air state
void Aircraft::InAirUpdate(float DeltaTimeHours)
{
	std::cout << "Aircraft Type: " << EnumStringsCompany[static_cast<int>(mType)] << " Id: " << mId << " currently in air" << std::endl;

	//Stat keeping
	mNumFaults += DidFaultOccur(DeltaTimeHours) ? 1 : 0;
	float MilesTraveled = CRUISE_SPEEDS[static_cast<int>(mType)] * DeltaTimeHours;
	mPassengerDistanceTraveled += MilesTraveled * PASSENGER_COUNT[static_cast<int>(mType)];
	mTimeInFlight += DeltaTimeHours;

	//See if the battery needs to be charged
	mCurrBattery -= MilesTraveled * ENERGY_USE[static_cast<int>(mType)];
	if (mCurrBattery <= 0.0f)
	{
		for (int i = 0; i < MAX_CHARGERS; i++)
		{
			assert(mChargers[i] != nullptr);
			if (mChargers[i]->TryAcquire()) //Got the charger
			{
				mChargerAcquired[i] = true;
				mState = AircraftState::Charging;
				return;
			}

		}
		
		mState = AircraftState::WaitingToCharge;
		
	}
}

//Update function to handle the waiting-to-charge state
void Aircraft::WaitingToChargeUpdate(float DeltaTimeHours)
{
	std::cout << "Aircraft Type: " << EnumStringsCompany[static_cast<int>(mType)] << " Id: " << mId << " currently waiting to charge" << std::endl;

	//Stat keeping
	mTimeWaitingToCharge += DeltaTimeHours;

	//Try to find a charger
	for (int i = 0; i < MAX_CHARGERS; i++)
	{
		assert(mChargers[i] != nullptr);
		if (mChargers[i]->TryAcquire()) //Got the charger
		{
			mChargerAcquired[i] = true;
			mState = AircraftState::Charging;
			return;
		}
	}
}

//Base state manager. This should be replaced with a behavior tree in the future iterations
bool Aircraft:: StateManager(float DeltaTimeHours)
{
	if(DeltaTimeHours < 0.0f)
	{
		return false;
	}
	//std::cout<<DeltaTimeHours << std::endl;
	switch (mState)
	{
	case AircraftState::Charging:
		ChargingUpdate(DeltaTimeHours);
		break;
	case AircraftState::InAir:
		InAirUpdate(DeltaTimeHours);
		break;
	case AircraftState::WaitingToCharge:
		WaitingToChargeUpdate(DeltaTimeHours);
		break;
	}
	
	return true;
}
