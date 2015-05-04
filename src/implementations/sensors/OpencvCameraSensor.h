///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-FEB-26
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef OPENCV_CAMERA_SENSOR_H_
#define OPENCV_CAMERA_SENSOR_H_

#include "../drone_application/SensorManager.h"

#include <opencv2/opencv.hpp>
#include <mutex>
#include <thread>

typedef SensorTrait<SensorType::eVision, cv::Mat> VisionTrait;

class OpencvCameraSensor : public Sensor<VisionTrait>{
public:
	OpencvCameraSensor() : mCamera(0), mWatchThread(&OpencvCameraSensor::callback, this){ };
	OpencvCameraSensor(OpencvCameraSensor&){};
	~OpencvCameraSensor(){/*666 TODO stop thread*/ };

	cv::Mat get(){
		cv::Mat copyImg;
		mMutex.lock();
		mImage.copyTo(copyImg);
		mMutex.unlock();
		return copyImg;
	}

private:
	void callback(){
		for (;;){
			cv::Mat frame;
			mCamera >> frame;
			mMutex.lock();
			frame.copyTo(mImage);
			mMutex.unlock();

		}
	}

private:
	cv::Mat	mImage;
	std::mutex			mMutex;
	cv::VideoCapture	mCamera;
	std::thread			mWatchThread;
};

#endif	//	OPENCV_CAMERA_SENSOR_H_