#pragma once

//Constants

//Companies
enum Company
{
	Alpha,
	Beta,
	Charlie,
	Delta,
	Echo
};

const unsigned int MAX_COMPANIES = 5; 

//Aircraft type statistics
static const char * EnumStringsCompany[MAX_COMPANIES] = { "Alpha", "Beta", "Charlie", "Delta", "Echo" };
const float CRUISE_SPEEDS[MAX_COMPANIES] = { 120.f, 100.f, 160.f, 90.f, 30.f };
const float BATTERY_CAPACITY[MAX_COMPANIES] = { 320.f, 100.f, 220.f, 120.f, 150.f };
const float TIME_TO_CHARGE[MAX_COMPANIES] = { 0.6f, 0.2f, 0.8f, 0.62f, 0.3f };
const float ENERGY_USE[MAX_COMPANIES] = { 1.6f, 1.5f, 2.2f, 0.8f, 5.8f };
const unsigned int PASSENGER_COUNT[MAX_COMPANIES] = { 4, 5, 3, 2, 2 };
const float PROBABILITY_FAULT[MAX_COMPANIES] = { 0.25f, 0.1f, 0.05f,0.22f, 0.61f };

//Simulation parameters
const float REAL_TO_SIMULATED_TIME_SECONDS = 60.f;
const float TIME_TO_RUN_SIMULATION_SECONDS = 180.0f;

const unsigned int NUM_VEHICLES_DEPLOYED = 20;

//Shared resources
const unsigned int MAX_CHARGERS = 3; 
const unsigned int MAX_USERS_CHARGER = 1;


