///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	DroneApplication
//		Author:	Pablo Ramon Soria
//		Date:	2015-06-22
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _DRONE_APPLICATIONS_DRONE_LOG_H_
#define _DRONE_APPLICATIONS_DRONE_LOG_H_

#include <fstream>
#include <mutex>
#include <string>

#include <core/time/time.h>

/// Log shared through all application.
///
class DroneLog {
public:
	///\brief Init log with current time.
	static void			init();

	///\brief Get instance of log.
	static DroneLog*	get();

	///\brief Stop and close log.
	static void			end();

	///\brief Write message into log.
	///\param _tag: tag to identify message.
	///\param _msg: message writed to log.
	void write(std::string _tag, std::string _msg);

private:
	DroneLog();
	~DroneLog();

	static DroneLog *	mInstance;

	std::ofstream		mLog;
	std::mutex			mSecureMutex;

}

#endif	//	_DRONE_APPLICATIONS_DRONE_LOG_H_
