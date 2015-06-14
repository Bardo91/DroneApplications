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
const std::string cPosCmdTopic = "/mavros/setpoint_position/local";

//---------------------------------------------------------------------------------------------------------------------
MavrosController::MavrosController(){
	#if defined(_HAS_ROS_LIBRARIES_)
		ros::NodeHandle nHandle;
		mVelCmdPub = nHandle.advertise<geometry_msgs::TwistStamped>(cVelCmdTopic, 1000);
		mPosCmdPub = nHandle.advertise<geometry_msgs::PoseStamped>(cPosCmdTopic, 1000);
	#else
		std::cout << "[MAVROS_SENSOR] Library compiled without ROS dependencies. Mavros Sensor is dummy now" << std::endl;
	#endif
}

std::vector<double> decodeParameters(std::string _payload){
	std::vector<double> parameters;
	size_t index;
	while ((index = _payload.find(',')) != std::string::npos){
		parameters.push_back((double)atof(_payload.substr(0, index).c_str()));
		_payload = _payload.substr(index + 1, _payload.size());
	}

	return parameters;
}

//---------------------------------------------------------------------------------------------------------------------
void MavrosController::parseAction(const Message& _message){
	#if defined(_HAS_ROS_LIBRARIES_)

		std::vector<double> parameters = decodeParameters(_message.payload());

		switch (_message.type()) {
		case MessageType::eMoveVel:{
			geometry_msgs::TwistStamped msg;			
			msg.twist.linear = { parameters[0], parameters[1], parameters[2] };
			msg.twist.angular = { parameters[3], parameters[4], parameters[5] };
			mVelCmdPub.publish(msg);

			break;
		}case MessageType::eMoveLocal:{
			geometry_msgs::PoseStamped msg;
			msg.twist.linear = { parameters[0], parameters[1], parameters[2] };
			msg.twist.angular = { parameters[3], parameters[4], parameters[5], parameters[6] };
			mPosCmdPub.publish(msg);

			break;
		}case MessageType::eMoveGlobal:{
			std::cout << "[WARNING] Moving using global references is not implemented yet" << std::end;
			break;
		}default:
			std::cout << "[WARNING] Message of type: " << _message.type() << " is not supported in this controller." << std::endl;
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