#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"
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
		login(request);
	}
	else if(request.id == SIGNUP_CODE)
	{
		signup(request);
	}

	return result;
}

RequestResult LoginRequestHandler::login(Requestinfo ri)
{
	RequestResult result;
	LoginRequest Lr;
	LoginResponse response;
	Lr = JsonResponsePacketDeserializer::deserializeLoginRequest(ri.buffer);

	if(!m_loginManager.login(Lr.username, Lr.password));
	{	
		ErrorResponse err;
		err.message = "Error in login request.";
		throw err;
	}
	response.status = 100;

	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this; //probably need to change in v2

	return result;
}

RequestResult LoginRequestHandler::signup(Requestinfo ri)
{
	RequestResult result;
	SignupRequest sr;
	SignupResponse response;
	sr = JsonResponsePacketDeserializer::deserializeSignupRequest(ri.buffer);

	if(!m_loginManager.signup(sr.username, sr.password, sr.email));
	{
		ErrorResponse err;
		err.message = "Error in signup request.";
		throw err;
	}
	response.status = 100;

	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this; //probably need to change in v2

	return result;
}
