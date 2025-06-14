#include "MemberAndAdminRoomHandler.h"
#include "RequestHandlerFactory.h"


const RequestResult MemberAndAdminRoomHandler::getRoomState(const RequestInfo& ri)
{

	RequestResult result;
	GetRoomStateResponse getRoomStateResp;
	RoomData roomData;
	int id = m_room.getRoomData().id;
	try 
	{
		roomData = m_roomManager.getRoom(id).getRoomData();//oops

	}
	catch(...){
		LeaveRoomResponse leaveRoomResp;
		leaveRoomResp.status = STATUS_OK;
		result.response = JsonResponsePacketSerializer::serializeResponse(leaveRoomResp);
		result.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
		return result;
	}

	getRoomStateResp.status = STATUS_OK;
	getRoomStateResp.hasGameBegun = roomData.status;
	getRoomStateResp.players = m_roomManager.getRoom(id).getAllUsers();
	getRoomStateResp.questionCount = roomData.numOfQuestionsInGame;
	getRoomStateResp.answerTimeout = roomData.timePerQuestion;

	if (roomData.status == GAME_STARTED)
		result.newHandler = m_handlerFactory.createGameRequestHandler(m_user);
	else
		result.newHandler = this; // Last changed: V3

	result.response = JsonResponsePacketSerializer::serializeResponse(getRoomStateResp);

	return result;
}

MemberAndAdminRoomHandler::MemberAndAdminRoomHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user, const Room& room) : m_handlerFactory(handlerFactory), m_user(user), m_room(room), m_roomManager(handlerFactory.getRoomManager())
{
}


