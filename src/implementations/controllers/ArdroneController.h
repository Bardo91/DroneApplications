///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-APR-10
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef ARDRONE_CONTROLLER_H_
#define ARDRONE_CONTROLLER_H_

#include "../drone_application/Controller.h"
#include <drone/Ardrone.h>

class ArdroneController : public Controller{
public:
	void parseAction(const Message& _message);

private:
	ardronepp::Ardrone mDrone;
};


#endif	//	ARDRONE_CONTROLLER_H_