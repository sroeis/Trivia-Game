#include "JsonResponsePacketSerializer.h"



Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse Er)
{
	//using the macro to turn
	json J = Er;

	std::string JsonStr = J.dump();

	std::string BinaryStr = TurnToBinary(JsonStr);

	Buffer buffer(BinaryStr.begin(), BinaryStr.end());;
	
	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse Lr)
{
	//using the macro to turn
	json J = Lr;

	std::string JsonStr = J.dump();

	std::string BinaryStr = TurnToBinary(JsonStr);

	Buffer buffer(BinaryStr.begin(), BinaryStr.end());;

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse Sr)
{
	//using the macro to turn
	json J = Sr;

	std::string JsonStr = J.dump();

	std::string BinaryStr = TurnToBinary(JsonStr);

	Buffer buffer(BinaryStr.begin(), BinaryStr.end());;

	return buffer;
}

std::string JsonResponsePacketSerializer::TurnToBinary(std::string Str)
{

	std::string BinaryStr = "";

	for (char& _char : Str)
	{
		BinaryStr += std::bitset<8>(_char).to_string();
	}
	
	return BinaryStr;
}


