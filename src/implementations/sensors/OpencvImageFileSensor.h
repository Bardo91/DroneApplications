///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-MAR-09
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef OPENCV_IMAGE_FILE_SENSOR_H_
#define OPENCV_IMAGE_FILE_SENSOR_H_

#include "../drone_application/SensorManager.h"

#include <opencv2/opencv.hpp>
#include <mutex>
#include <thread>

typedef SensorTrait<SensorType::eVision, cv::Mat> VisionTrait;

class OpencvImageFileSensor : public Sensor<VisionTrait>{
public:
	OpencvImageFileSensor(std::string _nameTemplate, unsigned _counterInit) : mNameTemplate(_nameTemplate), mCounter(_counterInit){};
	OpencvImageFileSensor(OpencvImageFileSensor&){};
	~OpencvImageFileSensor(){/*666 TODO stop thread*/ };

	cv::Mat get(){
		std::stringstream fileName;
		fileName << mNameTemplate.substr(0, mNameTemplate.find("%d"));
		fileName << mCounter;
		fileName << mNameTemplate.substr(mNameTemplate.find("%d") + 2, mNameTemplate.npos);
		mCounter++;
		return cv::imread(fileName.str());
	}


private:
	cv::Mat				mImage;
	std::string			mNameTemplate;
	unsigned			mCounter;
};

#endif	//	OPENCV_IMAGE_FILE_SENSOR_H_