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
		result = login(request);
	}
	else if(request.id == SIGNUP_CODE)
	{
		result = signup(request);
	}

	return result;
}

RequestResult LoginRequestHandler::login(Requestinfo ri)
{
	RequestResult result;
	LoginRequest Lr;
	
	
	Lr = JsonResponsePacketDeserializer::deserializeLoginRequest(ri.buffer);

	if(m_handlerFactory.getLoginManager().login(Lr.username, Lr.password))
	{
		LoginResponse logResp;
		logResp.status = 100;

		result.response = JsonResponsePacketSerializer::serializeResponse(logResp);
		result.newHandler = this; //probably need to change in v2

		return result;

	}
	ErrorResponse errResp;
	errResp.message = "Error in login request.";
	result.response = JsonResponsePacketSerializer::serializeResponse(errResp);
	result.newHandler = this; //probably need to change in v2
	return result;
}

RequestResult LoginRequestHandler::signup(Requestinfo ri)
{
	RequestResult result;
	
	SignupRequest sr;
	sr = JsonResponsePacketDeserializer::deserializeSignupRequest(ri.buffer);
	if(m_handlerFactory.getLoginManager().signup(sr.username, sr.password, sr.email))
	{
		SignupResponse response;
		response.status = 100;
		result.response = JsonResponsePacketSerializer::serializeResponse(response);
		result.newHandler = this; //probably need to change in v2
		return result;
	}
	ErrorResponse errResp;
	errResp.message = "Error in signup request.";
	result.response = JsonResponsePacketSerializer::serializeResponse(errResp);
	result.newHandler = this; //probably need to change in v2
	return result;
}
