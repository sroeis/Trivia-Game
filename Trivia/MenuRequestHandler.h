#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
class RequestHandlerFactory; // Forward declaration
#include "RequestHandlerFactory.h"
#include <vector>
#include "Room.h"
using std::vector;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& factory, const LoggedUser& user) : m_handlerFactory(factory), m_user(user) {}
	bool isRequestRelevant(const RequestInfo& request) override;
	const RequestResult handleRequest(const RequestInfo& request) override;

private:
	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;
	static unsigned int m_newRoomId;

	const RequestResult signout(const RequestInfo& ri);
	const RequestResult getRooms(const RequestInfo& ri);
	const RequestResult getPlayersInRoom(const RequestInfo& ri);
	const RequestResult getPersonalStats(const RequestInfo& ri);
	const RequestResult getHighScore(const RequestInfo& ri);
	const RequestResult joinRoom(const RequestInfo& ri);
	const RequestResult createRoom(const RequestInfo& ri);
	const RequestResult deleteRoom(const RequestInfo& ri);

};