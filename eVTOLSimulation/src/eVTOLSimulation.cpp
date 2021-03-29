// eVTOLSimulation.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "eVTOLSimulation.h"
#include"SimManager.h"
#include"SimConstants.h"

int main()
{
	SimManager NewSimulation;
	if (NewSimulation.Init())
	{
		NewSimulation.Run(TIME_TO_RUN_SIMULATION_SECONDS, REAL_TO_SIMULATED_TIME_SECONDS);
		NewSimulation.PrintStats();
	}
	return 0;
}
