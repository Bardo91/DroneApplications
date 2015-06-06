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
MavrosSensor::MavrosSensor(){
	ros::NodeHandle nHandle;
	mTopicReader = nHandle.subscribe<catec_msgs::UALStateStamped>("/mavros/imudata/data", 0, &MavrosSensor::topicReaderCallback, this);
}

//---------------------------------------------------------------------------------------------------------------------
ImuData MavrosSensor::get(){
	std::lock_guard<std::mutex> lock(mSecureMutex);
	return mLastData;
}

//---------------------------------------------------------------------------------------------------------------------
void MavrosSensor::topicReaderCallback(const catec_msgs::UALStateStamped &_message){
	// Get data...
}