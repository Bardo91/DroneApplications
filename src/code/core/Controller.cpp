///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	DroneApplication
//		Author:	Pablo Ramon Soria
//		Date:	2015-APR-10
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include  "Controller.h"

//---------------------------------------------------------------------------------------------------------------------
Controller::Controller() : Loggeable("Controller") {

}

//---------------------------------------------------------------------------------------------------------------------
void Controller::set(std::priority_queue<Message, std::vector<Message>, Message> *_msgQueue){
	mMsgQueue = _msgQueue;
	mThread = new std::thread([this](){
		while (mControlling){
			if (mMsgQueue->size() != 0){
				mControlMutex.lock();
				parseAction(mMsgQueue->top());
				mMsgQueue->pop();
				mControlMutex.unlock();
			}
		}

	});

	write2Log("Set as controller");
}

//---------------------------------------------------------------------------------------------------------------------
void Controller::stop(){
	mControlling = false;
	write2Log("Stopping controller");
}
