///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-02-05
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//



#include "DroneApplication.h"


//---------------------------------------------------------------------------------------------------------------------
void DroneApplication::addCommand(const Message& _message){
	mQueueGuard.lock();
	mQueuedMessages.push(_message);
	mQueueGuard.unlock();
}

//---------------------------------------------------------------------------------------------------------------------
void DroneApplication::step(){
	// Intentionally blank
}

//---------------------------------------------------------------------------------------------------------------------

void DroneApplication::registerSensor(SensorBase& _sensor){ 
	mSensorManager.registerSensor(_sensor); 
};

//---------------------------------------------------------------------------------------------------------------------
void DroneApplication::setController(Controller& _controller){ 
	if (mCurrentController != nullptr){
		mCurrentController->stop();
		mCurrentController = nullptr;
	}
	_controller.set(&mQueuedMessages); 
	mCurrentController = &_controller;
};

//---------------------------------------------------------------------------------------------------------------------
void DroneApplication::attachProcess(TaskBase& _task){ 
	_task.attach(&mQueuedMessages, &mSensorManager); 
};

//---------------------------------------------------------------------------------------------------------------------