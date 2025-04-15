#pragma once
#include "LoginRequestHandler.h"
#include "Responses.h"


class JsonResponsePacketDeserializer
{
public:
	LoginRequest deserializeLoginRequest(Buffer buffer);
	SignupRequest deserializeSignupRequest(Buffer buffer);
private:

};
