#pragma once

#include "IRequestHandler.h"
#include "Responses.h"
#include "RequestHandlerFactory.h"


class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(Requestinfo request);
	RequestResult handleRequest(Requestinfo request);
private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult login(Requestinfo ri);
	RequestResult signup(Requestinfo ri);
};