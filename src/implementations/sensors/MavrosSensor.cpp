///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-JUN-06
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


#include "MavrosSensor.h"


//---------------------------------------------------------------------------------------------------------------------
// Public interface
MavrosSensor::MavrosSensor(){
#if defined(_HAS_ROS_LIBRARIES)
	ros::NodeHandle nHandle;
	mTopicReader = nHandle.subscribe<catec_msgs::UALStateStamped>("/mavros/imudata/data", 0, &MavrosSensor::topicReaderCallback, this);
#else
	std::cout << "Library compiled without ROS dependencies. Mavros Sensor is dummy now" << std::endl;
#endif
}

//---------------------------------------------------------------------------------------------------------------------
ImuData MavrosSensor::get(){
	#if defined(_HAS_ROS_LIBRARIES)
		std::lock_guard<std::mutex> lock(mSecureMutex);
		return mLastData;
	#else
		return ImuData();
	#endif
}

//---------------------------------------------------------------------------------------------------------------------
// Private interface.
#if defined(_HAS_ROS_LIBRARIES)
void MavrosSensor::topicReaderCallback(const catec_msgs::UALStateStamped &_message){
	// Get data...
}


#endif