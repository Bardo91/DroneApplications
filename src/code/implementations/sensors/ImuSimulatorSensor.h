///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-MAY-05
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#ifndef IMU_SIMULATOR_SENSOR_H_
#define IMU_SIMULATOR_SENSOR_H_

#include "ImuSensor.h"

#include <array>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>

bool dropLineIntoBuffer(std::ifstream& _inFile, double* _buffer);

typedef SensorTrait<SensorType::eIMU, ImuData> ImuTrait;

class ImuSimulatorSensor : public Sensor<ImuTrait>{
public:
	ImuSimulatorSensor(std::string _fileName) {
		mFile.open(_fileName);
		assert(mFile.is_open());
	};
	ImuSimulatorSensor(ImuSimulatorSensor&){};

	ImuData get(){
		double buffer[30];
		dropLineIntoBuffer(mFile, buffer);
		
		mData.mAltitude	= buffer[15]/1000;

		mData.mPos[0] = buffer[13] / 1000;
		mData.mPos[1] = buffer[14] / 1000;
		mData.mPos[2] = buffer[15] / 1000;

		mData.mEulerAngles[0] = buffer[16];
		mData.mEulerAngles[1] = buffer[17];
		mData.mEulerAngles[2] = buffer[18];

		return mData;
	}

private:
	std::ifstream mFile;
	ImuData mData;
};


//---------------------------------------------------------------------------------------------------------------------
// Private Functions definition
bool dropLineIntoBuffer(std::ifstream& _inFile, double* _buffer){
	std::string line;
	int colCounter = 0;
	int init = 0;
	int counter = 0;

	getline(_inFile, line);
	colCounter = line.size();

	if (colCounter < 0)
		return false;

	int index = 0;
	for (int i = 0; i < colCounter; i++) {
		if (((int)line.at(i)) == 9 || i >= colCounter-1) {
			std::string part = line.substr(init, i - init);
			_buffer[index] = atof(part.c_str());
			init = i + 1;
			counter++;
			index++;
		}
	}

	return true;
}

#endif	//	IMU_SIMULATOR_SENSOR_H_