#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

/*-------------------------------------------------------------------------------------------------------------------------------
Note: every version check the new handler of evry Request result, maybe a new handler was created that would be better to use
-------------------------------------------------------------------------------------------------------------------------------*/

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& request)
{
	if (request.id != LOGIN_CODE && request.id != SIGNUP_CODE)
	{
		return false;
	}

	return true;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& request)
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

RequestResult LoginRequestHandler::login(RequestInfo ri)
{
	RequestResult result;
	LoginRequest Lr;
	
	
	Lr = JsonResponsePacketDeserializer::deserializeLoginRequest(ri.buffer);

	if(m_handlerFactory.getLoginManager().login(Lr.username, Lr.password))
	{
		LoginResponse logResp;
		logResp.status = 100;

		result.response = JsonResponsePacketSerializer::serializeResponse(logResp);
		result.newHandler = this->m_handlerFactory.createMenuRequestHandler(Lr.username); //Last changed: V2

		return result;

	}
	ErrorResponse errResp;
	errResp.message = "Error in login request.";
	result.response = JsonResponsePacketSerializer::serializeResponse(errResp);
	result.newHandler = this; // Last changed V2
	return result;
}

RequestResult LoginRequestHandler::signup(RequestInfo ri)
{
	RequestResult result;
	
	SignupRequest sr;
	sr = JsonResponsePacketDeserializer::deserializeSignupRequest(ri.buffer);
	if(m_handlerFactory.getLoginManager().signup(sr.username, sr.password, sr.email))
	{
		SignupResponse response;
		response.status = 100;
		result.response = JsonResponsePacketSerializer::serializeResponse(response);
		result.newHandler = this->m_handlerFactory.createMenuRequestHandler(sr.username); // Last changed: V2
		return result;
	}
	ErrorResponse errResp;
	errResp.message = "Error in signup request.";
	result.response = JsonResponsePacketSerializer::serializeResponse(errResp);
	result.newHandler = this; // Last changed: V2
	return result;
}
