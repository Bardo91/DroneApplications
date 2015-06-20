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

struct ImuData{
	std::array<double, 3>	mEulerAngles;
	std::array<double, 2>	mPos;	// latitude and longitude
	double					mAltitude;
	std::array<double, 4>	mQuaternion;
};

typedef SensorTrait<SensorType::eIMU, ImuData> ImuTrait;


class ImuSensor : public Sensor<ImuTrait>{
public:		// Public Interface
	ImuSensor(){};
	ImuSensor(ImuSensor&) {};

	ImuData get(){
		std::lock_guard<std::mutex> lock(mSecureMutex);
		return mLastData;

	}

protected:	//	 Members
	std::mutex	mSecureMutex;
	ImuData		mLastData;
};

#endif	//	_DRONE_APPLICATIONS_IMPLEMENTATIONS_SENSORS_IMU_SENSOR_H_