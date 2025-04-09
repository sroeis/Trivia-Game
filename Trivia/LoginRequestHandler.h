#pragma once

#include "IRequestHandler.h"
#include "Responses.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(Requestinfo request);
	RequestResult handleRequest(Requestinfo request);
};