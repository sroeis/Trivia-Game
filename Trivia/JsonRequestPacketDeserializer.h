#pragma once
#include "LoginRequestHandler.h"
#include "Responses.h"

class JsonResponsePacketDeserializer : public LoginRequestHandler
{
public:
	static LoginRequest deserializeLoginRequest(Buffer buffer);
	static SignupRequest deserializeSignupRequest(Buffer buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(Buffer buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(Buffer buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(Buffer buffer);
};
