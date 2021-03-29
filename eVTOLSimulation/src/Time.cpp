#include"Time.h"

// Static Data Initialization
namespace
{
	bool s_isInitialized = false;
	//Clock variables
	int64_t s_TimePreviousFrame = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	float s_DeltaTime = 0.0f;
	float s_TimeElapsed = 0.0f;
}


// Time
float Time::GetTotalSecondsElapsed()
{
	
	return s_TimeElapsed;
}

float Time::GetSecondsElapsedThisFrame()
{

	return s_DeltaTime;
}

void Time::OnNewFrame()
{

	int64_t SysTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	s_DeltaTime = (static_cast<float>(SysTime - s_TimePreviousFrame)) / 1000.f; //Delta time in seconds
	s_TimePreviousFrame = SysTime;
	s_TimeElapsed += s_DeltaTime;
}


