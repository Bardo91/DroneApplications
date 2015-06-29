///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		DroneApplication
//			Author:	Pablo R.S.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include "BlackBoxTask.h"

//---------------------------------------------------------------------------------------------------------------------
void BlackBoxTask::init() {
	write2Log("Initializing");
	mBlackBox.open("BlackBox" + std::to_string(time(NULL)) + ".txt");
	mTimer	= BOViL::STime::get();
	
	mCamera = getSensor<OpencvSensor>();
	mImu	= getSensor<ImuSensor>();

	if (mCamera == nullptr) 
		write2Log("There's no camera attached to the system");
	if(mImu == nullptr)
		write2Log("There's no imu sensor attached to the system");
	write2Log("Initialized");
}

//---------------------------------------------------------------------------------------------------------------------
void BlackBoxTask::run() {
	cv::Mat image = mCamera->get();
	ImuData imuData = mImu->get();
	if (mCamera != nullptr) 
		mBlackBox << "[" << mTimer->getTime() << "] " << "Got image. Width: " << image.cols << ", height: " << image.rows << std::endl;
	if(mImu != nullptr)
		mBlackBox << "[" << mTimer->getTime() << "] " <<  imuData.serialize() << std::endl;

	mTimer->mDelay(30);
	write2Log("Stored information into BlackBox");

}

