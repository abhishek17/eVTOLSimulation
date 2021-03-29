#ifndef CHARGER
#define CHARGER

#include<atomic>

//This class controls the simulation resource: chargers ; using the semaphore methodology
class Charger
{
private:
	int mMaxCount;
 	std::atomic<int> mCount;


public:
	Charger(unsigned int MaxCount);
	~Charger();
	bool TryAcquire();
	//This function assumes that the entity has the control of the resource to release it
	void Release();
};

#endif //CHARGER
