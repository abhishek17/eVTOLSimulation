#ifndef SIM_MANAGER
#define SIM_MANAGER

#include <pthread.h>
#include <inttypes.h>
#include"CommonStructs.h"
#include"Time.h"
#include"AircraftManager.h"
#include"SimConstants.h"
#include"Charger.h"

//Data needed by the airplanes from the simulation manager
struct ThreadData
{
	float mDeltaSimulatedTimeHour;
	Aircraft* mPlane;
};

//This class runs the simulation and acts as a central resource to delegate tasks. 
class SimManager
{
private:
	//Shared Resources
	Charger *mChargers[MAX_CHARGERS];

	//Aircraft operations
	Aircraft* mFleet[NUM_VEHICLES_DEPLOYED];
	AircraftManager mCompanies[MAX_COMPANIES];

	//Simulation threads
	pthread_t  mAircraftThreads[NUM_VEHICLES_DEPLOYED];
	
	//Sanity check variables
	bool mIsInitialized;
	


public:
	SimManager();
	~SimManager();

	//The central function to delegate tasks and keep a track of the simulation duration
	bool Run(float TimeToRunSimSeconds, float RealToSimulatedSeconds);
	bool Init();
	static void* ThreadedSim(void* Data);

	//Function to print the statistics when the simulation is done
	void PrintStats();

};

#endif //SIM_MANAGER
