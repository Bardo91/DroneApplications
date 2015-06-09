///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	DroneApplication
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

/**	Main class that holds Drone's application classes.	777 review pipeline.
*
*/
class DroneApplication{
public:
	/** \brief add new command to controller's queue.
	*	@param	_message: message to be added to the queue.
	*/
	void addCommand		(const Message& _message);
	
	/** \brief @deprecated
	*/
	void step			();

	/** \brief register new sensor in application.
	*	@param _sensor:	instance of sensor to be added.
	*/
	void registerSensor	(SensorBase& _sensor);
	
	/** \brief set new controller to drone's application. Only one controller can be assigned at once.
	*	@param _controller: instance of controller to be added.
	*/
	void setController	(Controller& _controller);
	
	/** \brief attach new task to drone's applcation. Currently only asynchronous tasks can be added.
	*	@param _task: task to be added.
	*/
	void attachProcess	(TaskBase& _task);
private:
	std::priority_queue<Message, std::vector<Message>, Message>		mQueuedMessages;
	SensorManager	mSensorManager;

	Controller		*mCurrentController = nullptr;

	std::mutex mQueueGuard;
};

#endif	//	DRONE_APPLICATION_H_