///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	DroneApplication
//		Author:	Pablo Ramon Soria
//		Date:	2015-06-22
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


#include "DroneLog.h"

#include <time.h>

//---------------------------------------------------------------------------------------------------------------------
// Static data initialization.
DroneLog* DroneLog::mInstance = nullptr;

//---------------------------------------------------------------------------------------------------------------------
void DroneLog::init() {
	if (mInstance == nullptr) {
		mInstance = new DroneLog();
	}
}

//---------------------------------------------------------------------------------------------------------------------
DroneLog * DroneLog::get() {
	return mInstance;
}

//---------------------------------------------------------------------------------------------------------------------
void DroneLog::end() {
	if (mInstance != nullptr) {
		delete mInstance;
	}
}

//---------------------------------------------------------------------------------------------------------------------
void DroneLog::write(std::string _tag, std::string _msg) {
	std::string entry = "[" + _tag + "] " + _msg;
	mSecureMutex.lock();
	mLog << entry << std::endl;
	mSecureMutex.unlock();
}

//---------------------------------------------------------------------------------------------------------------------
DroneLog::DroneLog() {
	time_t timer;
	time(&timer);
	std::string logName = "DroneLog_" + std::to_string(timer);
	mLog.open(logName);

}

//---------------------------------------------------------------------------------------------------------------------
DroneLog::~DroneLog() {
	mLog.close();
}

//---------------------------------------------------------------------------------------------------------------------