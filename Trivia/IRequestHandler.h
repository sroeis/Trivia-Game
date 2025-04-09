#pragma once

class IRequestHandler
{
	virtual bool isRequestRelevant(Requestinfo request) = 0;
	virtual RequestResult handleRequest(Requestinfo request) = 0;
};
