#pragma once

#include "IRequestHandler.h"
#include "Responses.h"
class RequestHandlerFactory; //forward declaration
#include "RequestHandlerFactory.h"


class LoginRequestHandler : public IRequestHandler
{
public:
    LoginRequestHandler(RequestHandlerFactory& factory) : m_handlerFactory(factory) {}
	bool isRequestRelevant(const Requestinfo& request) override;
	RequestResult handleRequest(const Requestinfo& request) override;
private:
	//LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult login(Requestinfo ri);
	RequestResult signup(Requestinfo ri);
};