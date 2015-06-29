///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		DroneApplication
//			Author:	Pablo R.S.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


#ifndef _DRONEAPPLICATIONS_IMPLEMENTATIONS_TASKS_BLACKBOXTASK_H_
#define _DRONEAPPLICATIONS_IMPLEMENTATIONS_TASKS_BLACKBOXTASK_H_

#include <fstream>
#include <Task.h>

#include <core/time/time.h>

#include "../sensors/ImuSensor.h"
#include "../sensors/OpencvSensor.h"

class BlackBoxTask : public Task<BlackBoxTask>{
public:
	void init();
	void run();

private:
	OpencvSensor	*mCamera;
	ImuSensor		*mImu;
	BOViL::STime	*mTimer;
	std::ofstream	mBlackBox;
};


#endif	//	_DRONEAPPLICATIONS_IMPLEMENTATIONS_TASKS_BLACKBOXTASK_H_

