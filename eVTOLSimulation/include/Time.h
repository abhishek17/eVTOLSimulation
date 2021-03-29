#ifndef TIME
#define TIME

#include<chrono>

//This namespace controls the timer functionalities. 
namespace Time
{
	float GetTotalSecondsElapsed();
	float GetSecondsElapsedThisFrame();

	void OnNewFrame();
	void Initialize();
}

#endif //TIME
