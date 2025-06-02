#include "MemberAndAdminRoomHandler.h"

const RequestResult MemberAndAdminRoomHandler::getRoomState(const RequestInfo& ri)
{
	RequestResult result;
	GetRoomStateResponse getRoomStateResp;
	RoomData roomData = m_room.getRoomData();

	getRoomStateResp.status = STATUS_OK;
	getRoomStateResp.hasGameBegun = roomData.status;
	getRoomStateResp.players = m_room.getAllUsers();
	getRoomStateResp.questionCount = roomData.numOfQuestionsInGame;
	getRoomStateResp.answerTimeout = roomData.timePerQuestion;

	result.newHandler = this; // Last changed: V3
	result.response = JsonResponsePacketSerializer::serializeResponse(getRoomStateResp);

	return result;
}


