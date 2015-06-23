///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	DroneApplication
//		Author:	Pablo Ramon Soria
//		Date:	2015-02-05
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//



#include "DroneApplication.h"
#include "DroneLog.h"

#include <sstream>
//---------------------------------------------------------------------------------------------------------------------
DroneApplication::DroneApplication() {
	DroneLog::init();

}

//---------------------------------------------------------------------------------------------------------------------
void DroneApplication::addCommand(const Message& _message){
	mQueueGuard.lock();
	mQueuedMessages.push(_message);
	mQueueGuard.unlock();

	//666 write2Log("Added new command to queue. Type: " + _message.type + ", Payload " + _message.payload());
}

//---------------------------------------------------------------------------------------------------------------------
void DroneApplication::step(){
	// Intentionally blank
}

//---------------------------------------------------------------------------------------------------------------------

void DroneApplication::registerSensor(SensorBase& _sensor){ 
	mSensorManager.registerSensor(_sensor); 

	std::stringstream ss;
	ss << "Registered new sensor: " << &_sensor;
	write2Log(ss.str());
};

//---------------------------------------------------------------------------------------------------------------------
void DroneApplication::setController(Controller& _controller){ 
	if (mCurrentController != nullptr){
		mCurrentController->stop();
		mCurrentController = nullptr;
	}
	_controller.set(&mQueuedMessages); 
	mCurrentController = &_controller;

	std::stringstream ss;
	ss << "Unregistered controller " << &mCurrentController << ". And registered new one: " << &_controller;
	write2Log(ss.str());
};

//---------------------------------------------------------------------------------------------------------------------
void DroneApplication::attachProcess(TaskBase& _task){ 
	_task.attach(&mQueuedMessages, &mSensorManager); 

	std::stringstream ss;
	ss << "Attached new process to application " << &_task;
	write2Log(ss.str());
};

//---------------------------------------------------------------------------------------------------------------------
void DroneApplication::write2Log(std::string _msg) {
	std::stringstream ss;
	ss << "DroneApplication-" << this;
	DroneLog::get()->write(ss.str(), _msg);
}

//---------------------------------------------------------------------------------------------------------------------