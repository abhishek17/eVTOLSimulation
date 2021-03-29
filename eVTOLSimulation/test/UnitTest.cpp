#include<assert.h>
#include"UnitTest.h"

void UnitTest:: TestAddAircraft()
{
	AircraftManager NewManager; 
	NewManager.SetCompany(Company::Alpha);
	Aircraft* NewAircraft;
	bool RetVal = NewManager.AddAircraft(nullptr,NewAircraft);
	//Check that when supplied no chargers, the function returns false
	assert(RetVal == false);
	//Check that when nothing is passed in, no new plane gets added
	assert(NewManager.GetNumAirplanes() == 0); 
}

void UnitTest:: TestAircraftStateManager()
{
	//The state manager should fail with a negative delta time
	Aircraft NewAircraft(Company::Alpha, 0);
	assert(NewAircraft.StateManager(-20.f) == false);
}

void UnitTest::TestSimRun()
{
	SimManager NewSimulation;
	//Simulation should return false when not initialized
	assert(NewSimulation.Run(10.f, 50.f) == false);
	if(NewSimulation.Init())
	{
		//Simulation should fail with negative timer values
		assert(NewSimulation.Run(-10.f, -50.f) == false);
	}
}

void UnitTest::TestThreadedSim()
{
	//The threaded sim function should return a failed error report when passed no data
	void* VoidReport = SimManager::ThreadedSim(nullptr);
	ErrorReport* Report = reinterpret_cast<ErrorReport*>(VoidReport);
	assert(Report->mDidSucceed == false);
}
