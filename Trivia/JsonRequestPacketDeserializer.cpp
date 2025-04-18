#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
#include <bitset>

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
	std::string BinaryStr = "";
	uint32_t size = 0;
	for (int i = SIZE_START; i < SIZE_END; ++i) //read the size 
	{
		size |= (buffer[i] << (8 * i));
	}

	for (int i = MSG_START; i < size + MSG_START; i++)
	{
		BinaryStr += buffer[i];
	}

	jsonStr = BinaryToString(BinaryStr);

	json parsed = json::parse(jsonStr);

	lr.username = parsed["username"];
	lr.password = parsed["password"];

	return lr;
}

SignupRequest JsonResponsePacketDeserializer::deserializeSignupRequest(Buffer buffer)
{
	SignupRequest sr;
	std::string jsonStr = "";
	std::string BinaryStr = "";
	uint32_t size = 0;
	for (int i = SIZE_START; i < SIZE_END; ++i) //read the size 
	{
		size |= (buffer[i] << (8 * i));
	}

	for (int i = MSG_START; i < size + MSG_START; i++)
	{
		BinaryStr += buffer[i];
	}

	jsonStr = BinaryToString(BinaryStr);

	json parsed = json::parse(jsonStr);

	sr.email = parsed["email"];
	sr.username = parsed["username"];
	sr.password = parsed["password"];

	return sr;
}

std::string JsonResponsePacketDeserializer::BinaryToString(std::string BinaryStr)
{
	std::string str = "";
	std::bitset<8> bits;
	for (int i = 0; i < BinaryStr.size(); i += 8)
	{
		bits = std::bitset<8>(BinaryStr.substr(i, 8));
		str += static_cast<char>(bits.to_ulong());
	}
	return str;


}
