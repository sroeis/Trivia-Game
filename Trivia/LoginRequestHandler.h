#pragma once

#include "IRequestHandler.h"
#include "Responses.h"
class RequestHandlerFactory; //forward declaration
#include "RequestHandlerFactory.h"


class LoginRequestHandler : public IRequestHandler
{
public:
    LoginRequestHandler(RequestHandlerFactory& factory) : m_handlerFactory(factory) {}
	bool isRequestRelevant(const RequestInfo& request) override;
	const RequestResult& handleRequest(const RequestInfo& request) override;
private:
	//LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
	const RequestResult& login(const RequestInfo& ri);
	const RequestResult& signup(const RequestInfo& ri);
};