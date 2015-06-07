///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-JUN-06
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef BARTASK_SENSORS_MAVROS_SENSOR_H_
#define BARTASK_SENSORS_MAVROS_SENSOR_H_

#include "../../SensorManager.h"

#if defined(_HAS_ROS_LIBRARIES)
	#include <ros/ros.h>	// 666 Check includes
	#include <c:/programming/safemobil_ws/sandbox/libs/grvc_catec/external_libs/rosCatec/include/catec_msgs/UALStateStamped.h>
#endif

#include <array>
#include <thread>
#include <mutex>

struct ImuData{
	std::array<double, 3> position;
	std::array<double, 3> orientation;
};

typedef SensorTrait<SensorType::eIMU, ImuData> MavrosSensorTrait;

class MavrosSensor : public Sensor<MavrosSensorTrait>{
public:		//	 Public interface
	MavrosSensor();

	ImuData get();

#if defined(_HAS_ROS_LIBRARIES)
private:	// Private methods
	void topicReaderCallback(const catec_msgs::UALStateStamped &_message);	// Check message type.

private:	// Members
	std::mutex	mSecureMutex;
	ImuData		mLastData;

	ros::Subscriber mTopicReader;
#endif
};


#endif	//	BARTASK_SENSORS_MAVROS_SENSOR_H_