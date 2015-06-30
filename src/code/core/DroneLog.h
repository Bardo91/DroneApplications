///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	DroneApplication
//		Author:	Pablo Ramon Soria
//		Date:	2015-06-22
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _DRONEAPPLICATIONS_CORE_DRONELOG_H_
#define _DRONEAPPLICATIONS_CORE_DRONELOG_H_

#include <fstream>
#include <mutex>
#include <string>

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

};

#endif	//	_DRONEAPPLICATIONS_CORE_DRONELOG_H_
