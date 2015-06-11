///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-02-05
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This is the main of the program.This program is an implementation to solve the trouble of catching bars
// in order to build afterwards structures.

#include <DroneApplication.h>
#include <implementations/sensors/MavrosSensor.h>

#include <iostream>
#include <sstream>

using namespace std;

int main(int _argc, char** _argv){
	#if defined(_HAS_ROS_LIBRARIES_)
		_argc; _argv;
		ros::init(_argc, _argv,"MavrosSensorTest");
	
		DroneApplication mainApp;
	
		MavrosSensor imuSensor;
	
		ros::Rate loop_rate(10);
	
		while(ros::ok()){
			mainApp.step();
			ImuData data = imuSensor.get();
			std::cout << data.mEulerAngles[0] << ", " << data.mEulerAngles[1] << ", " << data.mEulerAngles[2] << std::endl;
			ros::spinOnce();
			loop_rate.sleep();
		}
	#else
		std::cout << "[WARNING] Application compiled without ROS libraries" << std::endl;
		return -1;
	#endif
	//system("PAUSE");

}
