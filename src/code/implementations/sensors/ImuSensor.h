///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-JUN-07
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _DRONE_APPLICATIONS_IMPLEMENTATIONS_SENSORS_IMU_SENSOR_H_
#define _DRONE_APPLICATIONS_IMPLEMENTATIONS_SENSORS_IMU_SENSOR_H_

#include "../../SensorManager.h"

#include <array>
#include <mutex>

#include<cstring>

struct ImuData{
	std::array<double, 3>	mEulerAngles;
	std::array<double, 2>	mPos;	// latitude and longitude
	double					mAltitude;
	std::array<double, 4>	mQuaternion;

	std::array<double, 3>	mAngularSpeed;
	std::array<double, 3>	mLinearSpeed;

	std::array<double, 3>	mAngularAcc;
	std::array<double, 3>	mLinearAcc;

	double mTimeSpan;

	ImuData() {
		memset(this, 0, sizeof(ImuData));
	}

	std::string serialize() {
		std::stringstream ss;
		ss <<	"\t Euler: " << mEulerAngles[0] << ", " << mEulerAngles[1] << ", " << mEulerAngles[2] <<
				"\t Pos: " << mPos[0] << ", " << mPos[1] << ", " << mAltitude <<
				"\t Quaterion:" << mQuaternion[0] << ", " << mQuaternion[1] << ", " << mQuaternion[2] << ", " << mQuaternion[3];
		return ss.str();
	}

};

typedef SensorTrait<SensorType::eIMU, ImuData> ImuTrait;


class ImuSensor : public Sensor<ImuTrait>{
public:		// Public Interface
	ImuSensor(){ };
	ImuSensor(ImuSensor&) {};

	ImuData get(){
		std::lock_guard<std::mutex> lock(mSecureMutex);
		return mLastData;
	}

protected:
	void write2Log(std::string _msg) override {
		std::stringstream ss;
		ss << "ImuSensor-" << this;
		DroneLog::get()->write(ss.str(), _msg);
	}

protected:	//	 Members
	std::mutex	mSecureMutex;
	ImuData		mLastData;
};

#endif	//	_DRONE_APPLICATIONS_IMPLEMENTATIONS_SENSORS_IMU_SENSOR_H_