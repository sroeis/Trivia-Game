#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"

using json = nlohmann::json;

//from buffer format 
#define CODE_POS 0
#define SIZE_START 1 
#define SIZE_END 5
#define MSG_START 5

LoginRequest JsonResponsePacketDeserializer::deserializeLoginRequest(Buffer buffer)
{
	LoginRequest lr;
	std::string jsonStr = "";
	uint32_t size = 0;
	for (int i = SIZE_START; i < SIZE_END; ++i) //read the size 
	{
		size |= (buffer[i] << (8 * i));
	}

	for (int i = MSG_START; i < size + MSG_START; i++)
	{
		jsonStr += buffer[i];
	}

	json parsed = json::parse(jsonStr);

	lr.username = parsed["username"];
	lr.password = parsed["password"];

	return lr;
}

SignupRequest JsonResponsePacketDeserializer::deserializeSignupRequest(Buffer buffer)
{
	SignupRequest sr;
	std::string jsonStr = "";
	uint32_t size = 0;
	for (int i = SIZE_START; i < SIZE_END; ++i) //read the size 
	{
		size |= (buffer[i] << (8 * i));
	}

	for (int i = MSG_START; i < size + MSG_START; i++)
	{
		jsonStr += buffer[i];
	}

	json parsed = json::parse(jsonStr);

	sr.email = parsed["email"];
	sr.username = parsed["username"];
	sr.password = parsed["password"];

	return sr;
}

bool JsonResponsePacketDeserializer::isRequestRelevant(Requestinfo request)
{
	if (request.id != LOGIN_CODE && request.id != SIGNUP_CODE)
		return false;
	return true;
}

RequestResult JsonResponsePacketDeserializer::handleRequest(Requestinfo request)
{
	return RequestResult();
}
