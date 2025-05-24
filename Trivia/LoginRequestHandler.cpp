#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"
using std::exception;
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

const RequestResult LoginRequestHandler::handleRequest(const RequestInfo& request)
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

const RequestResult LoginRequestHandler::login(const RequestInfo& ri)
{
	RequestResult result;
	LoginRequest lr;
	
	
	lr = JsonResponsePacketDeserializer::deserializeLoginRequest(ri.buffer);
	try
	{
		if (m_handlerFactory.getLoginManager().login(lr.username, lr.password))
		{
			LoginResponse logResp;
			logResp.status = STATUS_OK;

			result.response = JsonResponsePacketSerializer::serializeResponse(logResp);
			result.newHandler = m_handlerFactory.createMenuRequestHandler(LoggedUser(lr.username)); //Last changed: V2
		}
	}
	catch (const exception e)
	{
		ErrorResponse errResp;
		errResp.message = e.what();
		result.response = JsonResponsePacketSerializer::serializeResponse(errResp);
		result.newHandler = this; // Last changed V2
	}
	return result;
}

const RequestResult LoginRequestHandler::signup(const RequestInfo& ri)
{
	RequestResult result;
	
	SignupRequest sr;
	sr = JsonResponsePacketDeserializer::deserializeSignupRequest(ri.buffer);
	try
	{
		if (m_handlerFactory.getLoginManager().signup(sr.username, sr.password, sr.email))
		{
			SignupResponse response;
			response.status = STATUS_OK;
			result.response = JsonResponsePacketSerializer::serializeResponse(response);
			result.newHandler = m_handlerFactory.createMenuRequestHandler(LoggedUser(sr.username)); // Last changed: V2
			return result;
		}
	}
	catch (const exception& e)
	{
		ErrorResponse errResp;
		errResp.message = e.what();
		result.response = JsonResponsePacketSerializer::serializeResponse(errResp);
		result.newHandler = this; // Last changed: V2
		return result;
	}
	
}
