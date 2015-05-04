///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-02-05
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef DRONE_APPLICATION_H_
#define DRONE_APPLICATION_H_

#include "Controller.h"
#include "Task.h"
#include "SensorManager.h"

#include <queue>
#include <mutex>

class DroneApplication{
public:
	void addCommand		(const Message& _message);
	void step			();

	void registerSensor	(SensorBase& _sensor);
	void setController	(Controller& _controller);
	void attachProcess	(TaskBase& _task);
private:
	std::priority_queue<Message, std::vector<Message>, Message>		mQueuedMessages;
	SensorManager	mSensorManager;

	Controller		*mCurrentController = nullptr;

	std::mutex mQueueGuard;
};

#endif	//	DRONE_APPLICATION_H_