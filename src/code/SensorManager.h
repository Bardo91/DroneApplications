///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	DroneApplication
//		Author:	Pablo Ramon Soria
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


#ifndef _SENSOR_MANAGER_H_
#define _SENSOR_MANAGER_H_

#include "Loggeable.h"
#include "Message.h"
#include "Sensor.h"

#include <cassert>
#include <iostream>
#include <map>
#include <vector>

/// Manager of Drone's sensors.
class SensorManager{
public:
	/// \brief register new sensor in the application.
	///	\param	_sensor: Instance of sensor to be registered.
	void registerSensor(SensorBase& _sensor);

	/// \brief get sensor of given type.
	///	\param _type: type of desired sensor.
	SensorBase* get(SensorType _type);

private:
	std::map<SensorType, SensorBase*> mRegisterdSensors;

};



#endif	//	_SENSOR_MANAGER_H_