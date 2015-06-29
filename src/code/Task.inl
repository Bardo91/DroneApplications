///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	DroneApplication
//		Author:	Pablo Ramon Soria
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

//---------------------------------------------------------------------------------------------------------------------
template<typename SensorClassType_>
SensorClassType_* TaskBase::getSensor(){ 
	return ((SensorClassType_*)(mSensorManager->get(SensorClassType_::Trait::Type))); 
};

//---------------------------------------------------------------------------------------------------------------------
template<typename SonClass_>
void Task<SonClass_>::start(){
	mThread = new std::thread(&SonClass_::run, reinterpret_cast<SonClass_*>(this));
	mIsRunning = true;
	write2Log("Starting Task");
}

//---------------------------------------------------------------------------------------------------------------------
template<typename SonClass_>
void Task<SonClass_>::stop(){
	mIsRunning = stop;
	if(mThread->joinable())
		mThread->join();

	write2Log("Task Stoped");
}

//---------------------------------------------------------------------------------------------------------------------
template<typename SonClass_>
void Task<SonClass_>::callback(){
	init();

	while (mIsRunning) {
		run();
	}
}