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
		mAltitudeSubscription	= nHandle.subscribe<sensor_msgs::Imu>("/mavros/imu/data", 0, &MavrosSensor::imuCallback, this);
		mImuSubscription		= nHandle.subscribe<sensor_msgs::NavSatFix>("/mavros/global_position/global ", 0, &MavrosSensor::positionCallback, this);
		mPositionSubscription	= nHandle.subscribe<std_msgs::Float64>("/mavros/global_position/rel_alt ", 0, &MavrosSensor::altitudeCallback, this);
	#else
		std::cout << "Library compiled without ROS dependencies. Mavros Sensor is dummy now" << std::endl;
	#endif
}

//---------------------------------------------------------------------------------------------------------------------
// Private interface.
#if defined(_HAS_ROS_LIBRARIES)

void MavrosSensor::altitudeCallback	(const std_msgs::Float64::ConstPtr& _msg){
	std::lock_guard<std::mutex> lock(mSecureMutex);
	mLastData.mAltitude = _msg.data;
}

//---------------------------------------------------------------------------------------------------------------------
void MavrosSensor::imuCallback		(const sensor_msgs::Imu::ConstPtr& _msg){
	std::lock_guard<std::mutex> lock(mSecureMutex);
	std::array<double,4> q = {_msg.orientation.x, _msg.orientation.y, _msg.orientation.z, _msg.orientation., w};
	mLastData.mEulerAngles[0] = atan2(2*(q[0]*q[1] + q[2]*q[3]), 1-2*(q[1]*q[1] + q[2]*q[2]));
	mLastData.mEulerAngles[1] = asin(2*(q[0]*q[2] - q[3]*q[1]));
	mLastData.mEulerAngles[2] = atan2(2*(q[0]*q[3] + q[1]*q[2]), 1-2*(q[2]*q[2] + q[3]*q[3]));;
}

//---------------------------------------------------------------------------------------------------------------------
void MavrosSensor::positionCallback(const sensor_msgs::NavSatFix::ConstPtr& _msg){
	std::lock_guard<std::mutex> lock(mSecureMutex);
	mLastData.mPos[0] = _msgs.latitude;
	mLastData.mPos[1] = _msgs.longitude;
}

#endif