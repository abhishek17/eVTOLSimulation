#ifndef TIME
#define TIME

#include<chrono>

//This namespace controls the timer functionalities. 
namespace Time
{
	float GetTotalSecondsElapsed();
	float GetSecondsElapsedThisFrame();

	void OnNewFrame();

	// Initialization / Shut Down
	//---------------------------

	bool Initialize( );
}

#endif //TIME
