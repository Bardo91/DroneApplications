///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
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

enum class SensorType { eIMU = 0x00, eVision=0x01, eLaser=0x02, eUltraSonic=0x03, ePressure=0x04 };

//---------------------------------------------------------------------------------------------------------------------
// Trait
template<SensorType SensorType_, typename DataType_>
struct SensorTrait{
	//using DataType = DataType_;
	typedef DataType_ DataType;
	static const SensorType Type = SensorType_;
};

//---------------------------------------------------------------------------------------------------------------------
// Sensor classes
class SensorBase{
public:
	SensorType type(){ return mType; };
protected:
	SensorBase(SensorType _type){ mType = _type; };
private:
	SensorType mType;
};

//---------------------------------------------------------------------------------------------------------------------
template<typename SensorTrait_>
class Sensor: public SensorBase{
public:
	typedef SensorTrait_ Trait;

	Sensor() :SensorBase(static_cast<SensorType>(Trait::Type)){};
	virtual typename Trait::DataType get() = 0;
};

//---------------------------------------------------------------------------------------------------------------------
// Sensor Manager Class
class SensorManager{
public:
	void registerSensor(SensorBase& _sensor){
		auto it = mRegisterdSensors.find(_sensor.type());
		if (it != mRegisterdSensors.end()){
			std::cout << "Error: This kind of sensor is already registered." << std::endl;
			return;
		}

		mRegisterdSensors.emplace(_sensor.type(), &_sensor);
	}

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