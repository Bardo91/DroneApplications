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

#include "ImuSensor.h"

#define _HAS_ROS_LIBRARIES_

#if defined(_HAS_ROS_LIBRARIES_)
	#include <ros/ros.h>	// 666 Check includes
	#include <sensor_msgs/Imu.h>
	#include <sensor_msgs/NavSatFix.h>
	#include <std_msgs/Float64.h>
#endif

#include <array>
#include <thread>
#include <mutex>

class MavrosSensor : public ImuSensor{
public:		//	 Public interface
	MavrosSensor();

	#if defined(_HAS_ROS_LIBRARIES_)
	private:	// Private methods
		void imuCallback	(const sensor_msgs::Imu::ConstPtr& _msg);
		void positionCallback	(const sensor_msgs::NavSatFix::ConstPtr& _msg);
		void altitudeCallback	(const std_msgs::Float64::ConstPtr& _msg);

	private:	// Members
		std::mutex	mSecureMutex;

		ros::Subscriber mAltitudeSubscription, mImuSubscription, mPositionSubscription;
	#endif
};


#endif	//	BARTASK_SENSORS_MAVROS_SENSOR_H_