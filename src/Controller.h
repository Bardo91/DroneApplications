///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-APR-10
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Message.h"

#include <queue>
#include <mutex>
#include <thread>
#include <iostream>

class DroneApplication;

class Controller{
public:
	void set(std::priority_queue<Message, std::vector<Message>, Message> *_msgQueue);
	void stop();

	virtual void parseAction(const Message& _message) = 0;
private:
	std::priority_queue<Message, std::vector<Message>, Message> *mMsgQueue;
	std::thread	*mThread;
	bool mControlling = true;
	std::mutex mControlMutex;

};


#endif	//	_CONTROLLER_H_