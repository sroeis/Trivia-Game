#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
#include <bitset>

using json = nlohmann::json;

//from buffer format 
#define CODE_POS 0
#define SIZE_START 1 
#define SIZE_END 5
#define MSG_START 5

const LoginRequest JsonResponsePacketDeserializer::deserializeLoginRequest(const Buffer& buffer)
{
	LoginRequest lr;

	std::string jsonStr(buffer.begin(), buffer.end());

	json parsed = json::parse(jsonStr);

	// Extract data
	lr.username = parsed["username"];
	lr.password = parsed["password"];

	return lr;
}

const SignupRequest JsonResponsePacketDeserializer::deserializeSignupRequest(const Buffer& buffer)
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

const GetPlayersInRoomRequest JsonResponsePacketDeserializer::deserializeGetPlayersInRoomRequest(const Buffer& buffer)
{
	GetPlayersInRoomRequest req;

	std::string jsonStr(buffer.begin(), buffer.end());

	json parsed = json::parse(jsonStr);

	// Extract data
	req.roomId = parsed["roomId"];

	return req;
}

const JoinRoomRequest JsonResponsePacketDeserializer::deserializeJoinRoomRequest(const Buffer& buffer)
{
	JoinRoomRequest req;

	std::string jsonStr(buffer.begin(), buffer.end());

	json parsed = json::parse(jsonStr);

	// Extract data
	req.roomId = parsed["roomId"];

	return req;
}

const CreateRoomRequest JsonResponsePacketDeserializer::deserializeCreateRoomRequest(const Buffer& buffer)
{
	try {

		CreateRoomRequest req;

		std::string jsonStr(buffer.begin(), buffer.end());

		json parsed = json::parse(jsonStr);

		// Extract data
		req.roomName = parsed["roomName"];
		req.answerTimeOut = std::stoi(parsed["answerTimeout"].get<std::string>());
		req.maxUsers = std::stoi(parsed["maxPlayers"].get<std::string>());
		req.questionCount = std::stoi(parsed["questionCount"].get<std::string>());

		return req;
	}
	catch (const std::exception& e) {
		std::cerr << "Error deserializing CreateRoomRequest: " << e.what() << std::endl;
		throw; // Re-throw the exception for further handling
	}


}

const DeleteRoomRequest JsonResponsePacketDeserializer::deserializeDeleteRoomRequest(const Buffer& buffer)
{
	DeleteRoomRequest req;

	std::string jsonStr(buffer.begin(), buffer.end());

	json parsed = json::parse(jsonStr);

	// Extract data
	req.roomId = parsed["roomId"];

	return req;
}
