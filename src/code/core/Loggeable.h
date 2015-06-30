///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	DroneApplication
//		Author:	Pablo Ramon Soria
//		Date:	2015-06-23
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//



#ifndef _DRONEAPPLICATIONS_LOGGEABLE_H_
#define _DRONEAPPLICATIONS_LOGGEABLE_H_

#include <string>
#include <sstream>

#include "DroneLog.h"

/// Interface to define classes that can write to logs.
class Loggeable {
protected:
	Loggeable(std::string _baseTag) {
		mBaseTag = _baseTag;
	}

	/// \brief Write to log message _msg.
	/// \param _msg: message to be written.
	virtual void write2Log(std::string _msg) {
		std::stringstream ss;
		ss << mBaseTag << "-" << this;
		DroneLog::get()->write(ss.str(), _msg);
	}

private:
	std::string mBaseTag;
};


#endif	//	_DRONEAPPLICATIONS_LOGGEABLE_H_