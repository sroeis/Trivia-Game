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
	RequestResult handleRequest(const RequestInfo& request) override;

private:
	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;
	static unsigned int m_roomCounter;

	RequestResult signout(const RequestInfo& ri);
	RequestResult getRooms(const RequestInfo& ri);
	RequestResult getPlayersInRoom(const RequestInfo& ri);
	RequestResult getPersonalStats(const RequestInfo& ri);
	RequestResult getHighScore(const RequestInfo& ri);
	RequestResult joinRoom(const RequestInfo& ri);
	RequestResult createRoom(const RequestInfo& ri);
};