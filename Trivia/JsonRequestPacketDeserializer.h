#pragma once
#include "LoginRequestHandler.h"
#include "Responses.h"

class JsonResponsePacketDeserializer 
{
public:
	static const LoginRequest deserializeLoginRequest(const Buffer& buffer);
	static const SignupRequest deserializeSignupRequest(const Buffer& buffer);
	static const GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(const Buffer& buffer);
	static const JoinRoomRequest deserializeJoinRoomRequest(const Buffer& buffer);
	static const CreateRoomRequest deserializeCreateRoomRequest(const Buffer& buffer);
	static const DeleteRoomRequest deserializeDeleteRoomRequest(const Buffer& buffer);
	static const LeaveRoomRequest deserializeLeaveRoomRequest(const Buffer& buffer);
	static const SubmitAnswerRequest deserializeSubmitAnswerRequest(const Buffer& buffer);

};
