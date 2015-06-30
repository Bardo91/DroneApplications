///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	DroneApplication
//		Author:	Pablo Ramon Soria
//		Date:	2015-02-05
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _DRONEAPPLICATIONS_CORE_MESSAGE_H_
#define _DRONEAPPLICATIONS_CORE_MESSAGE_H_

#include <string>
// Messages:
//		0x00:		Bad message
//		0x01-0xAF:	System messages
//		0xB0-0xCF:	Flight messages
//		0xD0-0xEF:	Sensor messages
//		0xF0-0xFF:	Free message type

enum MessageType {
	eBadMessage = 0x00,
	eStopExecution = 0x01,
	eTakeOff = 0xB0, eLanding = 0xB1, ePosition = 0xB2, eMove = 0xB3, eHovering = 0xB4, eMoveVel = 0xB5, eMoveGlobal = 0xB6, eMoveLocal = 0xB7,
	eVisionSensor=0xD0, eLaserSensor=0xD1, eUltrasonicSensor=0xD2
};

class Message{
public:
	Message(){};
	Message(const std::string& _raw){
		std::string raw = _raw;
		unsigned index = 0;

		// Decode msg: priority;type;payload;
		mLenght =	_raw.size();

		index =		raw.find(";");
		mPriority = atoi(raw.substr(0, index).c_str());

		raw =		raw.substr(index + 1, mLenght);
		index =		raw.find(";");
		mType =		atoi(raw.substr(0, index).c_str());
		
		if (index == std::string::npos){
			mPayload = "";
			return;
		}

		raw =		raw.substr(index + 1, mLenght);
		index =		raw.find(";");
		mPayload = raw.substr(0, index).c_str();
	}
	Message(unsigned _lenght, unsigned _type, unsigned _priority, std::string _payload){
		mLenght =	_lenght;
		mType =		_type;
		mPriority = _priority;
		mPayload =	_payload;
	}

	bool operator() (Message _msg1, Message _msg2){ return _msg1.priority() > _msg2.priority(); }

public:
	unsigned	lenght()	const { return mLenght; };
	unsigned	priority()	const { return mPriority; };
	unsigned	type()		const {return mType;};
	std::string payload()	const {return mPayload;};

private:
	unsigned	mLenght;
	unsigned	mPriority;
	unsigned	mType;
	std::string mPayload;
};

#endif	//	_DRONEAPPLICATIONS_CORE_MESSAGE_H_