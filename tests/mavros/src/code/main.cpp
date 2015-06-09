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
	_argc; _argv;
	DroneApplication mainApp;
	
	MavrosSensor imuSensor;
	
	for (;;){
		mainApp.step();
	}

	//system("PAUSE");

}
