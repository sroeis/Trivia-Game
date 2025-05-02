#include "JsonResponsePacketSerializer.h"



Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse er)
{
	//using the macro to turn
	json j = er;

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(ERROR_CODE, jsonBuff);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse lr)
{
	//using the macro to turn
	json j = lr;

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(LOGIN_CODE, jsonBuff);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse sr)
{
	//using the macro to turn
	json j = sr;

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(SIGNUP_CODE, jsonBuff);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(LogoutResponse lr)
{
	json j = lr; // lr must contain the status 1. check if its like that from the source that the req is sent from

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(LOGOUT_CODE, jsonBuff);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse r)
{
	return Buffer();
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse pr)
{
	json j = pr;

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(LOGOUT_CODE, jsonBuff);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse jr)
{
	json j = jr;

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(LOGOUT_CODE, jsonBuff);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse cr)
{
	json j = cr;

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(LOGOUT_CODE, jsonBuff);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse gr)
{
	json j = gr;

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(LOGOUT_CODE, jsonBuff);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetPersonalStatsResponse gr)
{
	json j = gr;

	std::string jsonStr = j.dump();

	Buffer jsonBuff(jsonStr.begin(), jsonStr.end());

	Buffer buffer = PackIntoBuffer(LOGOUT_CODE, jsonBuff);

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



