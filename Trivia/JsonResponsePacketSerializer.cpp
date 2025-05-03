#include "JsonResponsePacketSerializer.h"



Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& er)
{
	//using the macro to turn
	json j = er;

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(ERROR_CODE, jsonBuff);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LoginResponse& lr)
{
	//using the macro to turn
	json j = lr;

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(LOGIN_CODE, jsonBuff);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const SignupResponse& sr)
{
	//using the macro to turn
	json j = sr;

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(SIGNUP_CODE, jsonBuff);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LogoutResponse& lr)
{
	json j = lr; // lr must contain the status 1. check if its like that from the source that the req is sent from

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(LOGOUT_CODE, jsonBuff);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomsResponse& r)
{
	json j = r;

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(GET_ROOMS_CODE, jsonBuff);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse& pr)
{
	json j = pr;

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(GET_PLAYERS_IN_ROOM_CODE, jsonBuff);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse& jr)
{
	json j = jr;

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(JOIN_ROOM_CODE, jsonBuff);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const CreateRoomResponse& cr)
{
	json j = cr;

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(CREATE_ROOM_CODE, jsonBuff);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetHighScoreResponse& gr)
{
	json j = gr;

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(GET_HIGH_SCORE_CODE, jsonBuff);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetPersonalStatsResponse& gr)
{
	json j = gr;

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(GET_PERSONAL_STATS_CODE, jsonBuff);

	return buffer;
}



// Modified PackIntoBuffer to take Buffer (raw bytes) directly
Buffer JsonResponsePacketSerializer::PackIntoBuffer(int Code, const Buffer& payload)
{
	Buffer buffer;

	// Push the code 
	buffer.push_back(static_cast<unsigned char>(Code));

	// Push the Msg size 
	uint32_t size = payload.size();
	unsigned char sizeBytes[4];
	// Manually pack as little-endian
	sizeBytes[0] = size & 0xFF;
	sizeBytes[1] = (size >> 8) & 0xFF;
	sizeBytes[2] = (size >> 16) & 0xFF;
	sizeBytes[3] = (size >> 24) & 0xFF;
	buffer.insert(buffer.end(), sizeBytes, sizeBytes + 4);

	// Append the actual payload bytes
	buffer.insert(buffer.end(), payload.begin(), payload.end());

	return buffer;
}



