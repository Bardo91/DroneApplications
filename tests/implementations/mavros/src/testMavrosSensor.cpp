///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-02-05
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This is the main of the program.This program is an implementation to solve the trouble of catching bars
// in order to build afterwards structures.

#include <core/DroneApplication.h>
#include <implementations/sensors/MavrosSensor.h>
#include <core/time/time.h>

#include <iostream>
#include <sstream>
#include <thread>

using namespace std;

#if defined(_HAS_ROS_LIBRARIES_)
	// Define simulation of /mavros/imu/data topic
	ros::Publisher pubImu, pubAlt, pubPos;
	std::thread *publisher;
	bool publish = true;

	sensor_msgs::Imu imuData;
	sensor_msgs::Float64 altitude;
	sensor_msgs::NavSatFix navData;

	void initMockPublishers() {
		ros::NodeHandle nh;
		pubImu =nh.advertise<sensor_msgs::Imu>("/mavros/imu/data", 5);
		pubAlt =nh.advertise<sensor_msgs::Float64>("/mavros/global_position/rel_alt", 5);
		pubPos =nh.advertise<sensor_msgs::NavSatFix>("/mavros/global_position/global", 5);

		altitude.data		= 2.3;

		navData.latitude	= 0.5;
		navData.longitude	= 1.3;
		navData.altitude	= 2.3;

		imuData.orientation.x = 0.6;
		imuData.orientation.y = 0.7;
		imuData.orientation.z = 0.8;
		imuData.orientation.w = 0.9;

		publisher = new std::thread([]() {
			while (publish) {
				pubImu.publish(imuData);
				pubAlt.publish(altitude);
				pubPos.publish(navData);
			}
		});
	}

#endif


int main(int _argc, char** _argv){
	#if defined(_HAS_ROS_LIBRARIES_)
		_argc; _argv;
		ros::init(_argc, _argv,"MavrosSensorTest");
	
		initMockPublishers();

		DroneApplication mainApp;
	
		MavrosSensor imuSensor;
		ros::spin();
		BOViL::STime->get().mDelay(3000);
		ImuData data = imuSensor.get();
		
		// Check position.
		assert(data.mPos[0] == 0.5);
		assert(data.mPos[1] == 1.3);
		assert(data.mAltitude == 2.3);

		// Check euler angles.
		//assert(data.mPos[0] == 0.5);
		//assert(data.mPos[1] == 1.2);
		//assert(data.mAltitude == 2.3);

		// Check Quaternions
		assert(imuData.orientation.x == 0.6);
		assert(imuData.orientation.y == 0.7);
		assert(imuData.orientation.z == 0.8);
		assert(imuData.orientation.w == 0.9);
		
		publish = false;
		if (publisher->joinable()) {
			publisher->join();
		}
	#else
		std::cout << "[WARNING] Application compiled without ROS libraries" << std::endl;
		return -1;
	#endif
	//system("PAUSE");

}
