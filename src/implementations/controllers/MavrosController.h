///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-JUN-06
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef BARTASK_CONTROLLERS_MAVROS_CONTROLLER_H_
#define BARTASK_CONTROLLERS_MAVROS_CONTROLLER_H_

#include "../../Controller.h"

class MavrosController :public Controller {
public:		// Public Interface
	void parseAction(const Message& _message);

private:	// Private methods


private:	// Members
};

#endif	//	BARTASK_CONTROLLERS_MAVROS_CONTROLLER_H_