///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-JUN-06
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef BARTASK_CONTROLLERS_MAVROS_CONTROLLER_H_
#define BARTASK_CONTROLLERS_MAVROS_CONTROLLER_H_

#include "../../Controller.h"

#if defined(_HAS_ROS_LIBRARIES_)
	#include <ros/ros.h>	// 666 Check includes
	#include <geometry_msgs/TwistStamped.h>	// For velocity control
	#include <geometry_msgs/PoseStamped.h>	// For pose and attitude control
#endif

class MavrosController :public Controller {
public:		// Public Interface
	MavrosController();
	void parseAction(const Message& _message);

#if defined(_HAS_ROS_LIBRARIES_)
private:	// Private methods

private:	// Members
	std::mutex	mSecureMutex;

	ros::Publisher	mVelCmdPub, mPosCmdPub;
#endif

private:	// Members
};

#endif	//	BARTASK_CONTROLLERS_MAVROS_CONTROLLER_H_