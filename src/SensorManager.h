///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	DroneApplication
//		Author:	Pablo Ramon Soria
//		Date:	2015-02-05
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


#ifndef _SENSOR_MANAGER_H_
#define _SENSOR_MANAGER_H_

#include "Message.h"

#include <cassert>
#include <iostream>
#include <map>
#include <vector>

/** Defined types of sensors supported currently. 777 Review
*/
enum class SensorType { eIMU = 0x00, eVision=0x01, eLaser=0x02, eUltraSonic=0x03, ePressure=0x04 };

//---------------------------------------------------------------------------------------------------------------------
// Trait
/** Struct that defines sensor type and return type of sensor.
*/
template<SensorType SensorType_, typename DataType_>
struct SensorTrait{
	//using DataType = DataType_;
	typedef DataType_ DataType;
	static const SensorType Type = SensorType_;
};

//---------------------------------------------------------------------------------------------------------------------
// Sensor classes
/** Base sensor class that holds sensor type. Never used directly, defined for proper storing of different
*	types of sensors in maps and arrays.
*/
class SensorBase{
public:
	/** \brief get type of sensor.
	*/
	SensorType type(){ return mType; };
protected:
	SensorBase(SensorType _type){ mType = _type; };
private:
	SensorType mType;
};

//---------------------------------------------------------------------------------------------------------------------
/** Class that defines basic sensor interface.
*
*/
template<typename SensorTrait_>
class Sensor: public SensorBase{
public:
	typedef SensorTrait_ Trait;

	/** \brief Contructor
	*/
	Sensor() :SensorBase(static_cast<SensorType>(Trait::Type)){};
	
	/** \brief get last sensor's data.
	*/
	virtual typename Trait::DataType get() = 0;
};

//---------------------------------------------------------------------------------------------------------------------
// Sensor Manager Class
/** Manager of Drone's sensors.
*/

class SensorManager{
public:
	/** \brief register new sensor in the application.
	*	@param	_sensor: Instance of sensor to be registered.
	*/
	void registerSensor(SensorBase& _sensor){
		auto it = mRegisterdSensors.find(_sensor.type());
		if (it != mRegisterdSensors.end()){
			std::cout << "Error: This kind of sensor is already registered." << std::endl;
			return;
		}

		mRegisterdSensors.emplace(_sensor.type(), &_sensor);
	}

	/** \brief get sensor of given type.
	*	@param _type: type of desired sensor.
	*/
	SensorBase* get(SensorType _type){
		auto iterator = mRegisterdSensors.find(_type);
		if (iterator == mRegisterdSensors.end()){
			std::cout << "Error: There isn't any sensor of type: " << static_cast<unsigned>(_type) << " registered." << std::endl;
			assert(false);
		}

		return iterator->second;
	}

private:
	std::map<SensorType, SensorBase*> mRegisterdSensors;

};



#endif	//	_SENSOR_MANAGER_H_