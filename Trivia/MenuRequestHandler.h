#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& factory, const LoggedUser& user) : m_handlerFactory(factory), m_user(user) {}
	bool isRequestRelevant(const RequestInfo& request) override;
	RequestResult handleRequest(const RequestInfo& request) override;

private:
	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult signout(const RequestInfo& ri);
	RequestResult getRooms(const RequestInfo& ri);
	RequestResult getPlayersInRoom(const RequestInfo& ri);
	RequestResult getPersonalStats(const RequestInfo& ri);
	RequestResult getHighScore(const RequestInfo& ri);
	RequestResult joinRoom(const RequestInfo& ri);
	RequestResult createRoom(const RequestInfo& ri);
	
};