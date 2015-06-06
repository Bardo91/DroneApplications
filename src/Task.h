///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-02-07
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//



#ifndef TASK_H_
#define TASK_H_


#include "Message.h"
#include "SensorManager.h"

#include <queue>
#include <thread>

class DroneApplication;	// Forward declaration

class TaskBase{
public:
	void	queueMessage	(Message _message)	{ mDroneQueue->push(_message); };
	template<typename SensorClassType_>
	SensorClassType_* getSensor()	{ return ((SensorClassType_*)(mSensorManager->get(SensorClassType_::Trait::Type))); };

protected:
	friend class DroneApplication;
	TaskBase() {};
	void	attach(std::priority_queue<Message, std::vector<Message>, Message> *_queue, SensorManager *_sensorMgr) { mDroneQueue = _queue; mSensorManager = _sensorMgr; };

private:
	std::priority_queue<Message, std::vector<Message>, Message>		*mDroneQueue;
	SensorManager	*mSensorManager;
};


template<typename SonClass_>
class Task: public TaskBase{
public:
	virtual void run() = 0;
	void start(){
		mThread = new std::thread(&SonClass_::run, reinterpret_cast<SonClass_*>(this));
	}
private:
	std::thread		*mThread;
};

#endif	//	TASK_H_