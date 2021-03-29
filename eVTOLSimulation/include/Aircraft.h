#ifndef AIRCRAFT
#define AIRCRAFT

#include<iostream>
#include"SimConstants.h"
#include"Charger.h"

enum AircraftState
{
	InAir,
	Charging,
	WaitingToCharge
};

//This class handles the state changes as an aircraft goes through different stages of operation
class Aircraft
{
private:
	Company mType;
	Charger *mChargers[MAX_CHARGERS];
	bool mChargerAcquired[MAX_CHARGERS];
	unsigned int mId;

	//Simulation Record
	float mTimeInFlight;
	float mTimeCharging; 
	float mTimeWaitingToCharge; 
	int mNumFaults; 
	float mPassengerDistanceTraveled; 

	//Parameters to transition between different states
	AircraftState mState;
	float mCurrBattery;
	
	//Functions to manage aircraft states
	bool DidFaultOccur(float DeltaTimeHours);

	void ChargingUpdate(float DeltaTimeHours);
	void InAirUpdate(float DeltaTimeHours);
	void WaitingToChargeUpdate(float DeltaTimeHours);
	

public:
	Aircraft(Company Type, unsigned int Id);
	void Init(Charger *Chargers[MAX_CHARGERS]);

	//Functions to manage aircraft states
	bool StateManager(float DeltaTimeHours);


	//Getter functions
	inline float GetTimeInFlight()
	{
		return mTimeInFlight;
	}
	inline float GetTimeInCharging()
	{
		return mTimeCharging;
	}
	inline float GetTimeWaitingToCharge()
	{
		return mTimeWaitingToCharge;
	}
	inline int GetNumFaults()
	{
		return mNumFaults;
	}
	inline float GetPassengerDistanceTraveled()
	{
		return mPassengerDistanceTraveled;
	}

};
#endif //AIRCRAFT
