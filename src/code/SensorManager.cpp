///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	DroneApplication
//		Author:	Pablo Ramon Soria
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include "SensorManager.h"

//---------------------------------------------------------------------------------------------------------------------
void SensorManager::registerSensor(SensorBase& _sensor){
	auto it = mRegisterdSensors.find(_sensor.type());
	if (it != mRegisterdSensors.end()){
		std::cout << "Error: This kind of sensor is already registered." << std::endl;
		return;
	}

	mRegisterdSensors.emplace(_sensor.type(), &_sensor);
}
//---------------------------------------------------------------------------------------------------------------------
SensorBase* SensorManager::get(SensorType _type){
	auto iterator = mRegisterdSensors.find(_type);
	if (iterator == mRegisterdSensors.end()){
		std::cout << "Error: There isn't any sensor of type: " << static_cast<unsigned>(_type) << " registered." << std::endl;
		return nullptr;
	}

	return iterator->second;
}
//---------------------------------------------------------------------------------------------------------------------
