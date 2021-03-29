#ifndef CHARGER
#define CHARGER

#include <pthread.h>

//This class controls the simulation resource: chargers ; using the semaphore methodology
class Charger
{
private:
	int mVal;
	int mMaxCount;
	pthread_mutex_t mMutex;


public:
	Charger(unsigned int MaxCount);
	~Charger();
	bool TryAcquire();
	//This function assumes that the entity has the control of the resource to release it
	void Release();
};

#endif //CHARGER
