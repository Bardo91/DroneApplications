///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-JUN-06
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


#include "MavrosController.h"

const std::string cVelCmdTopic = "/mavros/setpoint_velocity/cmd_vel";
const std::string cPosCmdTopic = "/mavros/setpoint_attitude/attitude";
const std::string cAttCmdTopic = "/mavros/setpoint_position/local";

//---------------------------------------------------------------------------------------------------------------------
MavrosController::MavrosController(){
	#if defined(_HAS_ROS_LIBRARIES_)
		ros::NodeHandle nHandle;
		mVelCmdPub = nHandle.advertise<geometry_msgs::TwistStamped>(cVelCmdTopic, 1000);
		mPosCmdPub = nHandle.advertise<geometry_msgs::PoseStamped>(cPosCmdTopic, 1000);
		mAttCmdPub = nHandle.advertise<geometry_msgs::PoseStamped>(cAttCmdTopic, 1000);
	#else
		std::cout << "[MAVROS_SENSOR] Library compiled without ROS dependencies. Mavros Sensor is dummy now" << std::endl;
	#endif
}

//---------------------------------------------------------------------------------------------------------------------
void MavrosController::parseAction(const Message& _message){
	#if defined(_HAS_ROS_LIBRARIES_)
		switch (_message.type()) {
		case MessageType::eMove:{
			// Decode msgs
			geometry_msgs::TwistStamped msg;
			mVelCmdPub.publish(msg);
			break;
		}default:
			//std::cout << "Controller: Message of type: " << _message.type() << " is not supported in this controller." << std::endl;
			break;
		}
	#else
		std::cout << "[MAVROS_SENSOR] Library compiled without ROS dependencies. Mavros Sensor is dummy now" << std::endl;
	#endif
}

//---------------------------------------------------------------------------------------------------------------------


#if defined(_HAS_ROS_LIBRARIES_)

//---------------------------------------------------------------------------------------------------------------------


#endif