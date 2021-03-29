#include"Charger.h"

//Constructor
Charger::Charger(unsigned int MaxCount)
{

	//Intialize the charger to be available at the start
	mMaxCount = MaxCount;
	mCount = mMaxCount;
}

//Destructor
Charger::~Charger()
{

}

//Try to get the charger. If it`s busy, a false is relayed, instead of stalling the thread
bool Charger::TryAcquire()
{

	int count = mCount;
        if(count) 
        {
            return mCount.compare_exchange_strong(count, count - 1);
        } 
        else
        {
            return false;
        }
}

void Charger::Release()
{
	mCount++;
}

