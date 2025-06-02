#include "MenuRequestHandler.h"
#include "Responses.h"


/*-------------------------------------------------------------------------------------------------------------------------------
Note: every version check the new handler of evry Request result, maybe a new handler was created that would be better to use
-------------------------------------------------------------------------------------------------------------------------------*/

unsigned int MenuRequestHandler::m_newRoomId = 1;

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& request)
{
	return request.id == GET_ROOMS_CODE ||
		request.id == GET_PLAYERS_IN_ROOM_CODE ||
		request.id == CREATE_ROOM_CODE ||
		request.id == LOGOUT_CODE ||
		request.id == JOIN_ROOM_CODE ||
		request.id == GET_PERSONAL_STATS_CODE ||
		request.id == GET_HIGH_SCORE_CODE;
}

const RequestResult MenuRequestHandler::handleRequest(const RequestInfo& request)
{
    switch (request.id)
    {
	case CREATE_ROOM_CODE:
		return createRoom(request);
	case GET_ROOMS_CODE:
	    return getRooms(request);
	case GET_PLAYERS_IN_ROOM_CODE:
		return getPlayersInRoom(request);
	case GET_PERSONAL_STATS_CODE:
		return getPersonalStats(request);
	case LOGOUT_CODE:
		return signout(request);
	case JOIN_ROOM_CODE:
		return joinRoom(request);
	case CLOSE_ROOM_CODE:
		return deleteRoom(request);
	case GET_HIGH_SCORE_CODE:
		return getHighScore(request);
    }
}

const RequestResult MenuRequestHandler::signout(const RequestInfo& ri)
{
	m_handlerFactory.getLoginManager().logout(m_user.getUsername());
	RequestResult result;
	LogoutResponse logResp;
	logResp.status = STATUS_OK;
	result.response = JsonResponsePacketSerializer::serializeResponse(logResp);
	result.newHandler = m_handlerFactory.createLoginRequestHandler(); // Last changed: V2
	return result;
}

const RequestResult MenuRequestHandler::getRooms(const RequestInfo& ri)
{
	RequestResult result;
	GetRoomsResponse getRoomsResp;
	vector<Room> allRooms = m_handlerFactory.getRoomManager().getRooms();

	for (const auto& room : allRooms)
	{
		getRoomsResp.rooms.push_back(room.getRoomData());
	}
	getRoomsResp.status = STATUS_OK;

	// Serialize the response
	result.response = JsonResponsePacketSerializer::serializeResponse(getRoomsResp);
	result.newHandler = this; // Last changed: V2
	return result;
}

const RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& ri)
{
	RequestResult result;
	GetPlayersInRoomResponse getPlayersResp;
	GetPlayersInRoomRequest getPlayersReq = JsonResponsePacketDeserializer::deserializeGetPlayersInRoomRequest(ri.buffer);
	
	try
	{
		Room& room = m_handlerFactory.getRoomManager().getRoom(getPlayersReq.roomId);
		getPlayersResp.players = room.getAllUsers();

		result.response = JsonResponsePacketSerializer::serializeResponse(getPlayersResp);
		result.newHandler = this; // Last changed: V2
	}
	catch (std::out_of_range e)
	{
		ErrorResponse errorResp;
		errorResp.message = "Error, Room not found";
		result.response = JsonResponsePacketSerializer::serializeResponse(errorResp);
		result.newHandler = this; // Last changed: V2
	}

	return result;
}

const RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& ri)
{
	RequestResult result;
	GetPersonalStatsResponse getPersonalStatsResp;

	try
	{
		getPersonalStatsResp.statistics = m_handlerFactory.getStatisticsManager().getUserStatistics(m_user.getUsername());
		getPersonalStatsResp.status = STATUS_OK;

		// Serialize the response
		result.response = JsonResponsePacketSerializer::serializeResponse(getPersonalStatsResp);
		result.newHandler = this; // Last changed: V2
	}
	catch (std::out_of_range e)
	{
		ErrorResponse errorResp;
		errorResp.message = "Error, User not found";
		result.response = JsonResponsePacketSerializer::serializeResponse(errorResp);
		result.newHandler = this; // Last changed: V2
	}
	return result;
}

const RequestResult MenuRequestHandler::getHighScore(const RequestInfo& ri)
{
	GetHighScoreResponse getHighScoreResp;
	getHighScoreResp.statistics = m_handlerFactory.getStatisticsManager().getHighScore();
	getHighScoreResp.status = STATUS_OK;

	// Serialize the response
	RequestResult result;
	result.response = JsonResponsePacketSerializer::serializeResponse(getHighScoreResp);
	result.newHandler = this; // Last changed: V2

	return result;
}

const RequestResult MenuRequestHandler::joinRoom(const RequestInfo& ri)
{
	JoinRoomRequest joinRoomReq = JsonResponsePacketDeserializer::deserializeJoinRoomRequest(ri.buffer);
	RequestResult result;

	Room& room = m_handlerFactory.getRoomManager().getRoom(joinRoomReq.roomId);
	if (room.getRoomData().maxPlayers == room.getAllUsers().size())
	{
		ErrorResponse errorResp;
		errorResp.message = "Error, Room is full";
		result.response = JsonResponsePacketSerializer::serializeResponse(errorResp);
		result.newHandler = m_handlerFactory.createRoomMemberRequestHandler(m_user, room); // Last changed: V3
		return result;
	}
	else
	{
		JoinRoomResponse joinRoomResp;
		room.addUser(m_user.getUsername());
		joinRoomResp.status = STATUS_OK;
		result.response = JsonResponsePacketSerializer::serializeResponse(joinRoomResp);
		result.newHandler = this; // Last changed: V2
	}

	return result;
}

const RequestResult MenuRequestHandler::createRoom(const RequestInfo& ri)
{
	CreateRoomRequest createRoomReq = JsonResponsePacketDeserializer::deserializeCreateRoomRequest(ri.buffer);
	RoomData roomData;

	
	roomData.id = m_newRoomId++;
	roomData.maxPlayers = createRoomReq.maxUsers; 
	roomData.name = createRoomReq.roomName;
	roomData.numOfQuestionsInGame = createRoomReq.questionCount;
	roomData.timePerQuestion = createRoomReq.answerTimeOut;
	roomData.status = GAME_NOT_STARTED;
	m_handlerFactory.getRoomManager().CreateRoom(m_user, roomData);

	RequestResult result;
	CreateRoomResponse createRoomResp;
	createRoomResp.status = roomData.id;
	result.response = JsonResponsePacketSerializer::serializeResponse(createRoomResp);
	result.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_user, m_handlerFactory.getRoomManager().getRoom(roomData.id)); // Last changed: V3

	return result;
}


