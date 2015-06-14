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
#include <implementations/controllers/MavrosController.h>

#include <iostream>
#include <sstream>

using namespace std;

int main(int _argc, char** _argv){
	_argc; _argv;
	ros::init(_argc, _argv,"MavrosControllerTest");
	
	DroneApplication mainApp;
	
	MavrosController controller;
	
	ros::Rate loop_rate(10);
	
	Message msg(8, MessageType::eMove, 1, "");
	
	while(ros::ok()){
		mainApp.step();
		controller.parseAction(msg);
		ros::spinOnce();
		loop_rate.sleep();
	}

	//system("PAUSE");

}
