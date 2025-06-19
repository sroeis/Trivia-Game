#include "RoomAdminRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"
using std::exception;

const RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo& ri)
{
	RequestResult result;

	try
	{
		m_roomManager.deleteRoom(m_room.getRoomData().id);
		CloseRoomResponse response;
		response.status = STATUS_OK;
		result.response = JsonResponsePacketSerializer::serializeResponse(response);
		result.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	}
	catch (const exception& e)
	{
		ErrorResponse response;
		response.message = e.what();
		result.response = JsonResponsePacketSerializer::serializeResponse(response);
		result.newHandler = this;
	}

	return result;	
}

const RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& ri)
{
	RequestResult result;

	try
	{
		m_roomManager.getRoom(m_room.getRoomData().id).switchRoomState();

		StartGameResponse response;
		response.status = STATUS_OK;

		m_handlerFactory.getGameManager().createGame(m_roomManager.getRoom(m_room.getRoomData().id));

		result.response = JsonResponsePacketSerializer::serializeResponse(response);
		result.newHandler = m_handlerFactory.createGameRequestHandler(m_user);

	}
	catch (const exception& e)
	{
		ErrorResponse response;
		response.message = e.what();
		result.response = JsonResponsePacketSerializer::serializeResponse(response);
		result.newHandler = this;
	}

	return result;
}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& request)
{
	return  request.id == CLOSE_ROOM_CODE || request.id == START_GAME_CODE || request.id == GET_ROOM_STATE_CODE;
}

const RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& request)
{
	switch (request.id)
	{
	case CLOSE_ROOM_CODE:
		return closeRoom(request);
	case START_GAME_CODE:
		return startGame(request);
	case GET_ROOM_STATE_CODE:
		return getRoomState(request);

	}
}
