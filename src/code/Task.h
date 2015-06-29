///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	DroneApplication
//		Author:	Pablo Ramon Soria
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

//---------------------------------------------------------------------------------------------------------------------
///	Base task class that define asynchronous task interface. Never used directly, used to 
///	store tasks multiple types tasks in maps or arrays
class TaskBase: protected Loggeable{
public:
	/// \brief Queue new message to drone's controller queue (777 need revision). 
	void	queueMessage	(Message _message);

	/// \brief Get sensor of given template type  777 need revision to generalize in runtime not compile time.
	template<typename SensorClassType_>
	SensorClassType_* getSensor();

	virtual void start()	= 0;
	virtual void stop()		= 0;

protected:
	friend class DroneApplication;
	TaskBase();
	void	attach(std::priority_queue<Message, std::vector<Message>, Message> *_queue, SensorManager *_sensorMgr);

	std::thread		*mThread;
	bool			mIsRunning = false;

private:
	std::priority_queue<Message, std::vector<Message>, Message>		*mDroneQueue;
	SensorManager	*mSensorManager;
};

//---------------------------------------------------------------------------------------------------------------------
/// Task interface that implements the thread of the asyncronous tasks. 777 Add example.
template<typename SonClass_>
class Task: protected TaskBase{
public:
	/// \brief Task action. Loop is not implemented, task cycle is defined inside this method.
	virtual void init() = 0;
	virtual void run() = 0;

	/// \brief Start task.
	void start();
	void stop();
private:
	void callback();

};

#include "Task.inl"

#endif	//	TASK_H_