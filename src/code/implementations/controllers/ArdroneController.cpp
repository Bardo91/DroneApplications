///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-APR-10
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


#include "ArdroneController.h"

void ArdroneController::parseAction(const Message& _message){
	switch (_message.type())
	{
	case MessageType::eLanding:
		mDrone.control().land();
		break;
	case MessageType::eTakeOff:
		mDrone.control().takeOff();
		break;
	case MessageType::eHovering:
		mDrone.control().hovering();
		break;
	case MessageType::eMove:{
		std::string payload = _message.payload();
		float pitch = float(atof(payload.substr(0, payload.find(',')).c_str()));
		float roll = float(atof(payload.substr(payload.find(','), payload.size()).c_str()));
		mDrone.control().translate(pitch, roll);
		break;
	}default:
		//std::cout << "Controller: Message of type: " << _message.type() << " is not supported in this controller." << std::endl;
		break;
	}
}
