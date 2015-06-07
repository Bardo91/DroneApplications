///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	DroneApplication
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

/** Base interface of drone's controller.
*/
class Controller{
public:
	/** \brief	attach controller to drone's queue. @deprecated 777 need review.
	*/
	void set(std::priority_queue<Message, std::vector<Message>, Message> *_msgQueue);

	/** \brief Stop controller.
	*/
	void stop();

	/** \brief abstract method that decode messages and apply proper actions.
	*	@param _message: received message to be decoded.
	*/
	virtual void parseAction(const Message& _message) = 0;
private:
	std::priority_queue<Message, std::vector<Message>, Message> *mMsgQueue;
	std::thread	*mThread;
	bool mControlling = true;
	std::mutex mControlMutex;

};


#endif	//	_CONTROLLER_H_