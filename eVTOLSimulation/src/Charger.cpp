#include"Charger.h"

//Constructor
Charger::Charger(unsigned int MaxCount)
{
	pthread_mutex_init(&mMutex, NULL);

	//Intialize the charger to be available at the start
	mMaxCount = MaxCount;
	mVal = mMaxCount;
}

//Destructor
Charger::~Charger()
{
	pthread_mutex_destroy(&mMutex);

}

//Try to get the charger. If it`s busy, a false is relayed, instead of stalling the thread
bool Charger::TryAcquire()
{
	pthread_mutex_lock(&mMutex);


	if (mVal == 0)
	{
		return false;
	}
	else
	{
		mVal--;
		return true;
	}
	pthread_mutex_unlock(&mMutex);
}

void Charger::Release()
{
	pthread_mutex_lock(&mMutex);

	mVal++;
	pthread_mutex_unlock(&mMutex);
}

