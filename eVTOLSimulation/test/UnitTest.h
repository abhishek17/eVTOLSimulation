#ifndef UNIT_TEST
#define UNIT_TEST

#include"Aircraft.h"
#include"AircraftManager.h"
#include"SimManager.h"

class UnitTest
{
public:
	void TestAddAircraft();
	void TestAircraftStateManager();
	void TestSimRun();
	void TestThreadedSim();
};

#endif //UNIT_TEST
