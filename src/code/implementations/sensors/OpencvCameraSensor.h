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

#include "OpencvSensor.h"

#include <opencv2/opencv.hpp>
#include <mutex>
#include <thread>

class OpencvCameraSensor : public OpencvSensor{
public:
	OpencvCameraSensor() : mCamera(0), mIsRunning(true), mWatchThread(&OpencvCameraSensor::callback, this){ };
	OpencvCameraSensor(OpencvCameraSensor&){};
	~OpencvCameraSensor(){
		mIsRunning = false;
		if(mWatchThread.joinable())
			mWatchThread.join();
		mCamera.release();
	};

private:
	void callback(){
		while(mIsRunning){
			cv::Mat frame;
			mCamera >> frame;
			mMutex.lock();
			frame.copyTo(mImage);
			mMutex.unlock();
		}
	}

private:
	cv::VideoCapture	mCamera;
	bool				mIsRunning = false;
	std::thread			mWatchThread;
};

#endif	//	OPENCV_CAMERA_SENSOR_H_