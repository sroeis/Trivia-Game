#pragma once
#include "LoginRequestHandler.h"
#include "Responses.h"

class JsonResponsePacketDeserializer : public LoginRequestHandler
{
public:
	LoginRequest deserializeLoginRequest(Buffer buffer);
	SignupRequest deserializeSignupRequest(Buffer buffer);
	bool isRequestRelevant(Requestinfo request) override;
	RequestResult handleRequest(Requestinfo request) override;
private:

};
