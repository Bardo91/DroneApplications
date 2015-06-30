///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-APR-18
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef OCTO_ARCAS_CONTROLLER_H_
#define OCTO_ARCAS_CONTROLLER_H_

#include <core/Controller.h>
#include <core/comm/Socket.h>

//---------------------------------------------------------------------------------------------------------------------
struct OctoEulerMessage{
	unsigned int camera;
	double posX;
	double posY;
	double posZ;
	double phi;
	double theta;
	double psi;
	unsigned int heartBeat;
};

//---------------------------------------------------------------------------------------------------------------------
struct OctoQuaternionMessage {
	unsigned int camera;
	double posX;
	double posY;
	double posZ;
	double x;
	double y;
	double z;
	double w;
	unsigned int markerId;
};

//---------------------------------------------------------------------------------------------------------------------
class OctoArcasController: public Controller{
public:
	OctoArcasController();
	void parseAction(const Message& _message);

private:
	BOViL::comm::Socket *mOctoSocket;
};


#endif	//	OCTO_ARCAS_CONTROLLER_H_