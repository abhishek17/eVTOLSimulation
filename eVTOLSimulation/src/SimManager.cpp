#include<assert.h>
#include "SimManager.h"

//Constructor
SimManager::SimManager()
{
	mIsInitialized = false;
	for (unsigned int i = 0; i < MAX_CHARGERS; i++)
	{
		mChargers[i] = new Charger(MAX_USERS_CHARGER);
	}
}

SimManager::~SimManager()
{
	for (unsigned int i = 0; i < MAX_CHARGERS; i++)
	{
		delete(mChargers[i]);
	}
}

//Initializes the simulation
bool SimManager::Init()
{
	//Lamda to calculate a random number between 0 and MAX_COMPANIES
	auto RandomNumber = [](unsigned int SeedAddition, unsigned int MaxNum) -> int
	{
		srand(static_cast<unsigned int>(SeedAddition + std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
		return rand() % MaxNum;
	};
	
	//Initialize aircraft companies
	mCompanies[0].SetCompany(Company::Alpha);
	mCompanies[1].SetCompany(Company::Beta);
	mCompanies[2].SetCompany(Company::Charlie);
	mCompanies[3].SetCompany(Company::Delta);
	mCompanies[4].SetCompany(Company::Echo);

	//Initalize time
	Time::Initialize();

	//Deploy aircrafts
	for (unsigned int i = 0; i < NUM_VEHICLES_DEPLOYED; i++)
	{
		int RandomAircraftType = RandomNumber(i, MAX_COMPANIES);
		if (!mCompanies[RandomAircraftType].AddAircraft(mChargers, mFleet[i]))
		{
			std::cout << "ERROR! Could not deploy aircraft" << std::endl;
			return false;
		}
	}
	mIsInitialized = true;
	return true;
}

//Run the simulation
bool SimManager:: Run(float TimeToRunSimSeconds, float RealToSimulatedSeconds)
{
	if(TimeToRunSimSeconds <= 0.0f)
	{
		std::cout<< "Simulation time cannot be less than 0" << std::endl;
		return false;
	}
	if(RealToSimulatedSeconds <= 0.0f)
	{
		std::cout<< "Simulation scale cannot be less than 0" << std::endl;
		return false;
	}
	if(!mIsInitialized)
	{
		std::cout<< "Simulation can`t start as the simulation engine has not been initialzed" << std::endl;
		return false;
	}
	while (Time::GetTotalSecondsElapsed() <= TimeToRunSimSeconds)
	{
		Time::OnNewFrame();

		//Data structure to get information from the main thread to aicraft threads
		ThreadData* ThdData[NUM_VEHICLES_DEPLOYED];
		//Run threads
		for (unsigned int i = 0; i < NUM_VEHICLES_DEPLOYED; i++)
		{
			assert(mFleet[i] != nullptr);
			ThdData[i] = new ThreadData;
			if (ThdData[i] == nullptr)
			{
				std::cout << "ERROR!! Can`t allocate data to run threads" << std::endl;
				return false;
			}
			//Provide the thread function with delta time and the aircraft information
			ThdData[i]->mDeltaSimulatedTimeHour = (Time::GetSecondsElapsedThisFrame() * RealToSimulatedSeconds) / 3600.f;
			ThdData[i]->mPlane = mFleet[i];

			pthread_create(&(mAircraftThreads[i]), NULL, &ThreadedSim, (void*)(ThdData[i]));

		}

		//Join threads
		for (unsigned int i = 0; i< NUM_VEHICLES_DEPLOYED; i++)
		{
			pthread_join(mAircraftThreads[i], NULL);
			
		}
		//Delete thread data
		for (unsigned int i = 0; i< NUM_VEHICLES_DEPLOYED; i++)
		{
			if (ThdData[i] != nullptr)
			{
				delete(ThdData[i]);
				ThdData[i] = nullptr;    // Ensure address is not reused.
			}
		}
		std::cout << std::endl << "Update for threads is done" << std::endl;
	}

	return true;
}

//Threaded function to delgate state operations for aircrafts
void* SimManager::ThreadedSim(void* Data)
{

	ThreadData *UsefulData = reinterpret_cast<ThreadData*>(Data);
	if(UsefulData == nullptr)
	{
		LastErrorReported.mErrorMessage = "The threaded simulation functionality failed because of null data" ;
		LastErrorReported.mDidSucceed = false;
		return reinterpret_cast<void*>(&LastErrorReported);
	}
	if(UsefulData->mPlane == nullptr)
	{
		LastErrorReported.mErrorMessage = "The threaded simulation functionality failed because of null aircraft" ;
		LastErrorReported.mDidSucceed = false;
		return reinterpret_cast<void*>(&LastErrorReported);
	}
	UsefulData->mPlane->StateManager(UsefulData->mDeltaSimulatedTimeHour);
	LastErrorReported.mDidSucceed = true;
	
	return reinterpret_cast<void*>(&LastErrorReported);
}

//Print simulation statistics
void SimManager::PrintStats()
{
	std::cout << std::endl << std::endl << "The simulation has ended. Here are the stats from different companies: " << std::endl << std::endl;
	for (unsigned int i = 0; i < MAX_COMPANIES; i++)
	{
		mCompanies[i].PrintStats();
	}
}
