///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	DroneApplication
//		Author:	Pablo Ramon Soria
//		Date:	2015-06-29
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


#ifndef _DRONEAPPLICATIONS_CORE_SENSOR_H_
#define _DRONEAPPLICATIONS_CORE_SENSOR_H_

/// Defined types of sensors supported currently. 777 Review

enum class SensorType { eIMU = 0x00, eVision=0x01, eLaser=0x02, eUltraSonic=0x03, ePressure=0x04 };

//---------------------------------------------------------------------------------------------------------------------
/// Struct that defines sensor type and return type of sensor.
template<SensorType SensorType_, typename DataType_>
struct SensorTrait{
	//using DataType = DataType_;
	typedef DataType_ DataType;
	static const SensorType Type = SensorType_;
};

//---------------------------------------------------------------------------------------------------------------------
/// Base sensor class that holds sensor type. Never used directly, defined for proper storing of different
///	types of sensors in maps and arrays.
class SensorBase{
public:
	/// \brief get type of sensor.
	
	SensorType type(){ return mType; };
protected:
	SensorBase(SensorType _type){ mType = _type; };
private:
	SensorType mType;
};

//---------------------------------------------------------------------------------------------------------------------
/// Class that defines basic sensor interface.
template<typename SensorTrait_>
class Sensor: public SensorBase, private Loggeable{
public:
	typedef SensorTrait_ Trait;

	/// \brief Contructor
	Sensor() :SensorBase(static_cast<SensorType>(Trait::Type)), Loggeable("Sensor"){};

	/// \brief get last sensor's data.
	virtual typename Trait::DataType get() = 0;
};

#endif	//	 _DRONEAPPLICATIONS_CORE_SENSOR_H_