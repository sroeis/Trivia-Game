#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
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
		LoginResponse response;
		Lr = JsonResponsePacketDeserializer::deserializeLoginRequest(request.buffer);

		response.status = 100;

		result.response = JsonResponsePacketSerializer::serializeResponse(response);
	}
	else if(request.id == SIGNUP_CODE)
	{
		SignupRequest Sr;
		SignupResponse response;
		Sr = JsonResponsePacketDeserializer::deserializeSignupRequest(request.buffer);

		response.status = 100;
		result.response = JsonResponsePacketSerializer::serializeResponse(response);
	}

	return result;
}
