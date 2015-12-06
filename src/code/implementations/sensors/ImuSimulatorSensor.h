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

#include "../../SensorManager.h"
#include "ImuSensor.h"
#include <array>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>

bool dropLineIntoBuffer(std::ifstream& _inFile, double* _buffer);

typedef SensorTrait<SensorType::eIMU, ImuData> ImuTrait;

class ImuSimulatorSensor : public ImuSensor{
public:
	ImuSimulatorSensor(std::string _fileName) {
		mFile.open(_fileName);
		assert(mFile.is_open());
	};
	ImuSimulatorSensor(ImuSimulatorSensor&){};

	ImuData get(){
		double buffer[30];
		dropLineIntoBuffer(mFile, buffer);
		std::array<double,4> q = {buffer[2], buffer[3], buffer[4], buffer[5]};

		mData.mQuaternion[0] = q[0];
		mData.mQuaternion[1] = q[1];
		mData.mQuaternion[2] = q[2];
		mData.mQuaternion[3] = q[3];

		mData.mEulerAngles[0] = atan2(2*(q[0]*q[1] + q[2]*q[3]), 1-2*(q[1]*q[1] + q[2]*q[2]));
		mData.mEulerAngles[1] = asin(2*(q[0]*q[2] - q[3]*q[1]));
		mData.mEulerAngles[2] = atan2(2*(q[0]*q[3] + q[1]*q[2]), 1-2*(q[2]*q[2] + q[3]*q[3]));;

		mData.mAngularSpeed[0] = buffer[12];
		mData.mAngularSpeed[1] = buffer[13];
		mData.mAngularSpeed[2] = buffer[14];

		mData.mLinearAcc[0] = buffer[9];
		mData.mLinearAcc[1] = buffer[10];
		mData.mLinearAcc[2] = buffer[11];

		mData.mPos3d[0] = buffer[18];
		mData.mPos3d[1] = buffer[19];
		mData.mPos3d[2] = buffer[20];

		mData.mAltitude = buffer[1];

		mData.mTimeSpan = buffer[0];

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