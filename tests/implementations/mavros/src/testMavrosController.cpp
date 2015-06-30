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
#include <implementations/controllers/MavrosController.h>

#include <iostream>
#include <sstream>

using namespace std;

int main(int _argc, char** _argv){
	_argc; _argv;
	#if defined(_HAS_ROS_LIBRARIES_)
		ros::init(_argc, _argv,"MavrosControllerTest");
	
		DroneApplication mainApp;
	
		MavrosController controller;
	
		ros::Rate loop_rate(10);
	

		Message msg1(23, MessageType::eMoveVel, 1, "1.0,0.0,0.0,0.0,0.0,0.0");	
		Message msg2(23, MessageType::eMoveVel, 1, "-1.0,0.0,0.0,0.0,0.0,0.0");	

		int counter = 0;
		while(ros::ok()){
			mainApp.step();
			if(counter < 200){	// Move ahead
				controller.parseAction(msg1);
			}else{	// Move back
				controller.parseAction(msg2);
			}
			
			ros::spinOnce();
			loop_rate.sleep();
			counter = (counter++) % 400;
		}
	#else
		std::cout << "[WARNING] Application compiled without ROS libraries" << std::endl;
		return -1;
	#endif

	//system("PAUSE");

}
