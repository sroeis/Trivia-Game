#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
#include <bitset>

using json = nlohmann::json;

//from buffer format 
#define CODE_POS 0
#define SIZE_START 1 
#define SIZE_END 5
#define MSG_START 5

LoginRequest JsonResponsePacketDeserializer::deserializeLoginRequest(const Buffer& buffer)
{
	LoginRequest lr;

	std::string jsonStr(buffer.begin(), buffer.end());

	json parsed = json::parse(jsonStr);

	// Extract data
	lr.username = parsed["username"];
	lr.password = parsed["password"];

	return lr;
}

SignupRequest JsonResponsePacketDeserializer::deserializeSignupRequest(const Buffer& buffer)
{
	SignupRequest sr;

	std::string jsonStr(buffer.begin(), buffer.end());

	json parsed = json::parse(jsonStr);

	// Extract data
	sr.username = parsed["username"];
	sr.password = parsed["password"];
	sr.email = parsed["email"];

	return sr;
}

GetPlayersInRoomRequest JsonResponsePacketDeserializer::deserializeGetPlayersInRoomRequest(const Buffer& buffer)
{
	GetPlayersInRoomRequest req;

	std::string jsonStr(buffer.begin(), buffer.end());

	json parsed = json::parse(jsonStr);

	// Extract data
	req.roomId = parsed["roomId"];

	return req;
}

JoinRoomRequest JsonResponsePacketDeserializer::deserializeJoinRoomRequest(const Buffer& buffer)
{
	JoinRoomRequest req;

	std::string jsonStr(buffer.begin(), buffer.end());

	json parsed = json::parse(jsonStr);

	// Extract data
	req.roomId = parsed["roomId"];

	return req;
}

CreateRoomRequest JsonResponsePacketDeserializer::deserializeCreateRoomRequest(const Buffer& buffer)
{
	CreateRoomRequest req;

	std::string jsonStr(buffer.begin(), buffer.end());

	json parsed = json::parse(jsonStr);

	// Extract data
	req.roomName = parsed["roomName"];
	req.answerTimeOut = parsed["answerTimeOut"];
	req.maxUsers = parsed["maxUsers"];
	req.questionCount = parsed["questionCount"];

	return req;
}
