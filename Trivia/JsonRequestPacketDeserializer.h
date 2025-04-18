#pragma once
#include "LoginRequestHandler.h"
#include "Responses.h"

class JsonResponsePacketDeserializer : public LoginRequestHandler
{
public:
	static LoginRequest deserializeLoginRequest(Buffer buffer);
	static SignupRequest deserializeSignupRequest(Buffer buffer);
private:
	static std::string BinaryToString(std::string BinaryStr);
};
