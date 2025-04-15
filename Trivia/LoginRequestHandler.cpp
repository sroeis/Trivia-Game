#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"

bool LoginRequestHandler::isRequestRelevant(Requestinfo request)
{
	if (request.id != LOGIN_CODE && request.id != SIGNUP_CODE)
	{
		return false;
	}

	return true;
}

RequestResult LoginRequestHandler::handleRequest(Requestinfo request)
{
	RequestResult result;


	if (request.id == LOGIN_CODE)
	{
		LoginRequest Lr;
		Lr = JsonResponsePacketDeserializer::deserializeLoginRequest(request.buffer);
	}
	else if(request.id == SIGNUP_CODE)
	{
		SignupRequest Sr;
		Sr = JsonResponsePacketDeserializer::deserializeSignupRequest(request.buffer);
	}

	return result;
}
