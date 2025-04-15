#pragma once

#include "IRequestHandler.h"
#include "Responses.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	virtual bool isRequestRelevant(Requestinfo request) = 0;
	virtual RequestResult handleRequest(Requestinfo request) = 0;
};