///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EUROARMS:	Bar Task
//		Author:	Pablo Ramon Soria
//		Date:	2015-APR-18
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


#include "OctoArcasController.h"
#include <string>

using namespace BOViL::comm;


const std::string cArduPilotPort = "44000";


//---------------------------------------------------------------------------------------------------------------------
OctoArcasController::OctoArcasController(){
	mOctoSocket = Socket::createSocket(eSocketType::clientUDP, cArduPilotPort);
}

//---------------------------------------------------------------------------------------------------------------------
void OctoArcasController::parseAction(const Message& _message){
	OctoQuaternionMessage outMsg;

	switch (_message.type()) {
	case MessageType::eMove:{
		std::string payload = _message.payload();

		outMsg.camera = atoi(payload.substr(0, payload.find(",")).c_str());
		payload = payload.substr(payload.find(",") + 1, payload.size());

		outMsg.markerId = atoi(payload.substr(0, payload.find(",")).c_str());
		payload = payload.substr(payload.find(",") + 1, payload.size());

		outMsg.posX = atof(payload.substr(0, payload.find(",")).c_str());
		payload = payload.substr(payload.find(",") + 1, payload.size());

		outMsg.posY = atof(payload.substr(0, payload.find(",")).c_str());
		payload = payload.substr(payload.find(",") + 1, payload.size());

		outMsg.posZ = atof(payload.substr(0, payload.find(",")).c_str());
		payload = payload.substr(payload.find(",") + 1, payload.size());

		outMsg.x = atof(payload.substr(0, payload.find(",")).c_str());
		payload = payload.substr(payload.find(",") + 1, payload.size());

		outMsg.y = atof(payload.substr(0, payload.find(",")).c_str());
		payload = payload.substr(payload.find(",") + 1, payload.size());

		outMsg.z = atof(payload.substr(0, payload.find(",")).c_str());
		payload = payload.substr(payload.find(",") + 1, payload.size());

		outMsg.w = atof(payload.c_str());

		char *raw = new char[sizeof(outMsg)];
		memcpy(raw, &outMsg, sizeof(outMsg));

		mOctoSocket->sendMsg(std::string(raw, sizeof(outMsg)));
	}
	default:
		std::cout << "Unknow message type" << std::endl;
		break;
	}
}
//---------------------------------------------------------------------------------------------------------------------